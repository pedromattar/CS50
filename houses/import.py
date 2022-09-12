# TODO
import csv
from sys import argv, exit
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(argv) > 2:
    print("Usage: python import.py argument")
    exit(1)
#open csv argv

with open(argv[1], "r") as file:
    table = {}
    table["name"] = ["", "", ""]
    table["house"] = {}
    table["birth"] = {}

    reader = csv.DictReader(file)
    for row in reader:
        for i in dict(row)["name"].split(" "):
            first = (dict(row)["name"].split(" ")[0])
            last = (dict(row)["name"].split(" ")[len(dict(row)["name"].split(" ")) - 1])
            middle = None
            house = dict(row)["house"]
            birth = dict(row)["birth"]
            if (dict(row)["name"].split(" ")[1]) != last:
                middle = (dict(row)["name"].split(" ")[1])
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
            first, middle, last, house, birth)


#db.execute("QUERY")