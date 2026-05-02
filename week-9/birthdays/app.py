import os
import sqlite3
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from jinja2 import pass_context

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    conn = sqlite3.connect("birthdays.db")
    cursor = conn.cursor()

    if request.method == "POST":

        name = request.form.get("name")
        month = request.form.get("month", 1)
        day = request.form.get("day", 1)

        if not name or not month or not day:
            return redirect("/")

        try:
            month, day = int(month), int(day)
        except ValueError:
            return redirect("/")
        
        if month < 1 or month > 12:
            return redirect("/")
        if day < 1 or day > 31:
            return redirect("/")
        
        cursor.execute("""
        INSERT INTO birthdays (name, month, day)
        values (?, ?, ?);
        """, (name, month, day))

        conn.commit()
        conn.close()
        
        return redirect("/")

    else:
        birthdays = cursor.execute("""
        SELECT name, month, day
        FROM birthdays;
        """).fetchall()

        conn.close()
        
        return render_template("index.html", birthdays=birthdays)

if __name__ == "__main__":
    app.run(debug=True)
