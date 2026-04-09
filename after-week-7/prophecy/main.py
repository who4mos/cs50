import csv
import sqlite3
import sys

if len(sys.argv) != 3:
    print(f"Usage: {sys.argv[0]} <csv file> <new db name>")
    sys.exit(1)

with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    con = sqlite3.connect(sys.argv[2])
    cur = con.cursor()

    with open("schema.sql") as schema:
        cur.executescript(schema.read())
        con.commit()
    
    houses = dict()
    house_id = 1
    for row in reader:
        # insert house if new, with its house head
        if row["house"] not in houses:
            houses[row["house"]] = (house_id, row["head"])
            cur.execute("""
            INSERT OR IGNORE INTO houses
            VALUES (?, ?, ?);
            """, (house_id, row["house"], houses[row["house"]][1]))
            con.commit()
            house_id += 1

        # insert student
        cur.execute("""
        INSERT OR IGNORE INTO students
        VALUES (?, ?)
        """, (int(row["id"]), row["student_name"]))
        con.commit()

        # insert student-house relation
        cur.execute("""
        INSERT OR IGNORE INTO house_assignments
        VALUES (?, ?);
        """, (row["id"], houses[row["house"]][0]))
        con.commit()

    con.close()
