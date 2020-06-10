import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT SUM(numofshares) AS shares, symbol, name FROM transactions WHERE user_id = :id GROUP BY symbol", id = session["user_id"])
    stocksValue = 0
    for row in rows:
        pricefinder = lookup(row["symbol"])
        row['price'] = pricefinder["price"]
        row['totalValue'] = round((row['price'] * row['shares']), 2)
        stocksValue += row['totalValue']

    print(rows)
    cash = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])
    #get current stock prices
    #get grand total
    myCash = round(cash[0]["cash"], 2)
    allTheMoney = myCash + stocksValue

    return render_template("index.html", rows=rows, cash=cash, myCash = myCash, allTheMoney = allTheMoney)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        print("POSTED FROM BUY!!!")
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stockinfo = lookup(symbol)
        print("looked up stock")
        if stockinfo == None:
            return apology("Invalid stock name.")
            #name=info["name"], price=info["price"], symbol=info["symbol"]
        price = stockinfo["price"] * float(shares)
        print("price")
        print(price)
        #lookup users cash
        row = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        availableCash = float(row[0]["cash"])
        print(availableCash)
        newcash = availableCash - price
        time = datetime.now()
        if (price > availableCash):
            return apology("not enough money")
        db.execute("INSERT INTO transactions(user_id, symbol, name, numofshares, price, time) VALUES (:user_id, :symbol, :name, :numofshares, :price, :time)", user_id=session["user_id"], symbol=stockinfo["symbol"], name=stockinfo["name"], numofshares=shares, price=price, time=time)
        db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash = newcash, id = session["user_id"])
        print("cash updated")
        return redirect("/")

    if request.method == "GET":
        print("got")
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT numofshares, symbol, price, time FROM transactions WHERE user_id = :id", id = session["user_id"])
    return render_template("history.html", rows = rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        print("BACK IN QUOTE FOR SOME REASON")
        quote = request.form.get("symbol")
        info = lookup(quote)
        if info == None:
            return apology("Invalid stock name.")
        else:
            print(info)
            return render_template("quoted.html", name=info["name"], price=info["price"], symbol=info["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("You must provide a name.")
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) == 1:
            return apology("Username taken.")
        password = request.form.get("password")
        if not password:
            return apology("You must provide a password.")
        passwordConfirm = request.form.get("passwordConfirm")
        if not passwordConfirm:
            return apology("You must type password again.")
        if str(passwordConfirm) != str(password):
            return apology("Passwords must match.")
        hash = generate_password_hash(password)
        session["user_id"] = db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)", username=username, hash=hash)
        #return to main screen
        return redirect("/")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        rows = db.execute("SELECT symbol FROM transactions WHERE user_id = :id GROUP BY symbol", id = session["user_id"])
        return render_template("sell.html", rows=rows)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        totalShares = db.execute("SELECT SUM(numofshares) AS totalShares FROM transactions WHERE user_id = :id AND symbol = :symbol", id = session["user_id"], symbol = symbol)
        if (int(shares) > int(totalShares[0]['totalShares'])):
            return apology("You don't have that many shares")
        if (int(shares) < 0):
            return apology("Select a real number")
        stockinfo = lookup(symbol)
        if stockinfo == None:
            return apology("Invalid stock name.")
            #name=info["name"], price=info["price"], symbol=info["symbol"]
        price = stockinfo["price"] * float(shares)
        #lookup users cash
        row = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        availableCash = float(row[0]["cash"])
        print(availableCash)
        newcash = availableCash + price
        time = datetime.now()
        #need to get total shares or whatever if (shares > availableCash):
         #   return apology("not enough money")
        print(shares)
        shares = int(shares) * -1
        print("!!!SHARES!!!")
        print(shares)
        db.execute("INSERT INTO transactions(user_id, symbol, name, numofshares, price, time) VALUES (:user_id, :symbol, :name, :numofshares, :price, :time)", user_id=session["user_id"], symbol=stockinfo["symbol"], name=stockinfo["name"], numofshares=shares, price=price, time=time)
        db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash = newcash, id = session["user_id"])
        print("cash updated")
        return redirect("/")

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "GET":
        return render_template("deposit.html")
    if request.method == "POST":
        money = request.form.get("money")
        row = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        availableCash = float(row[0]["cash"])
        print(availableCash)
        newcash = availableCash + int(money)
        db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash = newcash, id = session["user_id"])
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
