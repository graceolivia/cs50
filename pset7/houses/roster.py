import csv
import sys
from cs50 import SQL

#import SQL 
db = SQL("sqlite:///students.db")

#check arguments
if len(sys.argv) != 2:
    print("Search for a House Roster, Please!")
    
#convert to string    
houseQuery = sys.argv[1]
    
#find students in order
studentsList = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", houseQuery)

#print
for rows in studentsList:
    if str(rows["middle"]) == 'None':
        print("{} {}, born {}".format(rows["first"], rows["last"], rows["birth"]))
    else:
        print("{} {} {}, born {}".format(rows["first"], rows["middle"], rows["last"], rows["birth"]))
    
