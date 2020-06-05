import csv
import sys
from cs50 import SQL

#import SQL
db = SQL("sqlite:///students.db")

#check if the correct number of arguements was passed
if len(sys.argv) != 2:
    print("Upload Student File, Please!")


#open CSV file
with open(sys.argv[1], 'r') as file:
    reader = csv.DictReader(file)

    #iteracte over csv
    for row in reader:
        #split name into sub-strings, store in nameList
        nameList = row["name"].split()
        #insert into table with 3 names
        if len(nameList) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", nameList[0], nameList[1], nameList[2], row["house"], row["birth"])
        if len(nameList) == 2:
            db.execute("INSERT INTO students(first, last, house, birth) VALUES(?, ?, ?, ?)", nameList[0], nameList[1], row["house"], row["birth"])

