import csv
import sqlite3

# get unique house/head pairs
houses = {}
with open("students.csv") as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if row["house"] not in houses:
            houses[row["house"]] = row["head"]
    

# create tables using schema file
con = sqlite3.connect("hogwarts.db")
cur = con.cursor()
with open("schema.sql") as script:
    querie = ""
    for line in script:
        querie += line
        if ';' in line:
            cur.execute(querie)
            querie = ""

# insert houses in its table
for house, head in houses.items():
    cur.execute("""
    INSERT OR IGNORE INTO houses (name, head)
    VALUES (?, ?)
    """, (house, head))
    con.commit()

# get house ids
house_ids = {}
res = cur.execute("SELECT name, id FROM houses;").fetchall()
for house, id in res:
    house_ids[house] = id
    
with open("students.csv") as csv_file:    
    reader = csv.DictReader(csv_file)

    for row in reader:
        # populate students table
        cur.execute("""
        INSERT OR IGNORE INTO students (id, name)
        VALUES (?, ?);
        """, (row["id"], row["student_name"]))

        # create relation between students and houses
        cur.execute("""
        INSERT OR IGNORE INTO house_assignments (student_id, house_id)
        VALUES (?, ?);
        """, (row["id"], house_ids[row["house"]]))
    con.commit()

con.close()
