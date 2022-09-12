# TODO
from sys import argv
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(argv) > 2:
    print("Usage: python import.py argument")
    exit(1)

#for i in (db.execute("SELECT first, middle, last, birth FROM students WHERE house=? ",argv[1])


for row in db.execute("SELECT first, middle, last, birth FROM students WHERE house=? GROUP BY first ORDER BY last, first", argv[1]):
    first = row["first"]
    middle = row["middle"]
    last = row["last"]
    birth = row["birth"]
    if row["middle"] == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")
