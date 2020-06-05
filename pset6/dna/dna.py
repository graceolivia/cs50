import sys
import csv

# check out the number of args
if len(sys.argv) != 3:
    print("First Argument: CSV file. Second Argument: DNA sequence.")

# read csv file into memory
with open(sys.argv[1], newline='') as file:
    # creates reader
    csvReader = csv.DictReader(file)
    # empty array to store dna
    database = []
    # read csv files into database, where they will be stored as csv
    for lines in csvReader:
        database.append(lines)
        

# open DNA file
with open(sys.argv[2]) as dnaFile:
    #store in memory
    dna = dnaFile.read()

# list to hold values
dnaStats = []

# make statsfinder


def statsfinder(x):
    miniDnas = database[0]
    for keys in miniDnas:
        index = 0
        newIndex = 0
        # the highest number of repeats so far
        highest = 0
        # convert keys to strings
        key = str(keys)
        # find locations of key in dna
        while index <= len(x) - len(key):
            index = x.find(key, newIndex, len(x))
            if index == -1:
                break
            # store the current number of repeats
            repeats = 0
            # check for repeats
            for a in range(index, len(x), (len(key))):
                # if substring is found
                if x.find(key, a, len(x)) == a:
                    repeats += 1
                # if substring is not found
                else:
                    if repeats > highest:
                        highest = repeats
                    #test this
                    newIndex = a + 1
                    if newIndex == index:
                        break
                    break

        # print("Repeats of {}: {}".format(key, highest))
        dnaStats.append(highest)
        print(highest)
            
        # the new place to start the search from
            
            
# make checker
def checker():
    for people in database:
        # hold the values of each thingy
        values = []
    # get the inner values
        for item in people:
            if item == 'name':
                values.append(0)
                continue
            else:
                values.append(int(people.get(item)))
        if values == dnaStats:
            print(people['name'])
            return

    print("No match.")


# get the dna stats
statsfinder(dna)

print(dnaStats)

# check it against the database
checker()