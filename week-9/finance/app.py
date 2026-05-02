import sqlite3
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

def create_transaction_and_holding_tables():
    conn = sqlite3.connect("finance.db")
    cursor = conn.cursor()

    # create transactions table if not exists
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    price FLOAT NOT NULL,
    shares INTEGER NOT NULL,
    transaction_date TEXT NOT NULL DEFAULT(datetime('now')),
    FOREIGN KEY (user_id) REFERENCES users(id)
    );
    """)
    conn.commit()

    # create holdings table if not exists
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS holdings (
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    shares INTEGER NOT NULL,
    PRIMARY KEY (user_id, symbol),
    FOREIGN KEY (user_id) REFERENCES users(id)
    );
    """)
    conn.commit()

    conn.close()
    

# create tables at server start (if they don't exist yet)
create_transaction_and_holding_tables()
    
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    conn = sqlite3.connect("finance.db")
    cursor = conn.cursor()

    cash = cursor.execute("""
    SELECT cash FROM users
    WHERE id = ?;
    """, (session["user_id"],)).fetchone()[0]
    
    rows = cursor.execute("""
    SELECT symbol, shares FROM holdings
    WHERE user_id = ?
    """, (session["user_id"],)).fetchall()

    conn.close()
    
    holdings = []
    total_cash = cash
    for symbol, shares in rows:
        quote = lookup(symbol)
        if quote:
            price = quote["price"]
            total_price = price * shares
            holdings.append({
                "symbol": symbol,
                "price": price,
                "shares": shares,
                "total_price": total_price
            })

            total_cash += total_price
    
    return render_template("index.html", cash=cash, total_cash=total_cash, holdings=holdings)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        conn = sqlite3.connect("finance.db")
        cursor = conn.cursor()

        # check if symbol is not empty and exists
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol must not be empty")
        symbol = symbol.upper()
        
        quote_data = lookup(symbol)
        if not quote_data:
            return apology("Symbol doesn't exist")

        # check if shares is not empty and is a positive integer
        shares = request.form.get("shares")
        if not shares:
            return apology("Shares must not be empty")

        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive integer")

        if shares < 1:
            return apology("Shares must be a positive integer")

        # check if user can afford purchase
        total_price = quote_data["price"] * shares
        user_cash = cursor.execute("""
        SELECT cash FROM users
        WHERE id = ?;
        """, (session["user_id"],)).fetchone()[0]

        if user_cash < total_price:
            return apology("You don't have money...")

        # insert purchase into transactions table
        cursor.execute("""
        INSERT INTO transactions (user_id, symbol, price, shares)
        VALUES (?, ?, ?, ?);
        """,
        (session["user_id"], symbol, quote_data["price"], shares))
        conn.commit()

        # update user's cash
        cursor.execute("""
        UPDATE users
        SET cash = cash - ?
        WHERE id = ?;
        """, (total_price, session["user_id"]))
        conn.commit()

        # check if user already holds some shares of that symbol
        holds = cursor.execute("""
        SELECT shares FROM holdings
        WHERE user_id = ? AND symbol = ?;
        """, (session["user_id"], symbol)).fetchall()

        if not holds:
            # create user/symbol pair
            cursor.execute("""
            INSERT INTO holdings (user_id, symbol, shares)
            VALUES (?, ?, ?);
            """, (session["user_id"], symbol, shares))
            conn.commit()
        else:
            # update user/symbol pair
            cursor.execute("""
            UPDATE holdings
            SET shares = shares + ?
            WHERE user_id = ? AND symbol = ?;
            """, (shares, session["user_id"], symbol))
            conn.commit()

        conn.close()
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    conn = sqlite3.connect("finance.db")
    cursor = conn.cursor()

    # get transactions to populate table
    rows = cursor.execute("""
    SELECT symbol, price, shares, transaction_date
    FROM transactions
    WHERE user_id = ?
    ORDER BY transaction_date DESC
    """, (session["user_id"],)).fetchall()

    transactions = []
    for symbol, price, shares, date in rows:
        transactions.append({
            "symbol": symbol,
            "price": price,
            "shares": shares,
            "date": date
        })
    
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        conn = sqlite3.connect("finance.db")
        cursor = conn.cursor()
        
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = cursor.execute(
            "SELECT id, hash FROM users WHERE username = ?", (request.form.get("username"),)).fetchall()

        # Ensure username exists
        if len(rows) != 1:
            return apology("invalid username", 403)

        user_id, hash = rows[0]
        print(user_id, hash)
        # Ensure password is correct
        if not check_password_hash(hash, request.form.get("password", "")):
            return apology("invalid password", 403)

        # Remember which user has logged in
        session["user_id"] = user_id

        conn.close()
        
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol must not be empty")
        
        quote_data = lookup(symbol)
        if not quote_data:
            return apology("Symbol doesn't exists")
        
        return render_template("quoted.html", quote_data=quote_data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        conn = sqlite3.connect("finance.db")
        cursor = conn.cursor()

        # check if username is not empty 
        username = request.form.get("username")
        if not username:
            return apology("username must not be empty")

        # check if username already exists
        rows = cursor.execute("""
        SELECT * FROM users
        WHERE username = ?;
        """, (username,)).fetchall()

        if len(rows) == 1:
            return apology("username already exists")

        # check if password and confirmation match
        password = request.form.get("password")

        confirmation = request.form.get("confirmation")
        if not password or not confirmation:
            return apology("password and confirmation must be filled in")
        
        if password != confirmation:
            return apology("confirmation doesn't match password")

        cursor.execute("""
        INSERT INTO users (username, hash)
        VALUES (?, ?)
        """, (username, generate_password_hash(password)))
        conn.commit()
        conn.close()

        return redirect("/")
    else:
        return render_template("register.html")        


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    conn = sqlite3.connect("finance.db")
    cursor = conn.cursor()
    
    if request.method == "POST":
        # get and validate symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must select a stock")

        # get and validate shares 
        shares = request.form.get("shares")
        if not shares:
            return apology("Shares must not be empty")

        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive integer")

        if shares < 1:
            return apology("Shares must be a positive integer")

        # get how many shares user have
        user_shares = cursor.execute("""
        SELECT shares FROM holdings
        WHERE user_id = ? AND symbol = ?;
        """, (session["user_id"], symbol)).fetchone()[0]

        if shares > user_shares:
            return apology("You don't have that many shares")

        # get stock price
        quote_data = lookup(symbol)
        if not quote_data:
            return apology("Could not get stock data")

        price = quote_data["price"]
        
        # insert sell into transactions table
        cursor.execute("""
        INSERT INTO transactions (user_id, symbol, price, shares)
        VALUES (?, ?, ?, ?);
        """, (session["user_id"], symbol, price, -shares))
        conn.commit()

        # update user's cash
        total_price = shares * price
        cursor.execute("""
        UPDATE users
        SET cash = cash + ?
        WHERE id = ?;
        """, (total_price, session["user_id"]))
        conn.commit()

        # update holdings table
        cursor.execute("""
        UPDATE holdings
        SET shares = shares - ?
        WHERE user_id = ? AND symbol = ?;
        """, (shares, session["user_id"], symbol))
        conn.commit()
        conn.close()
        
        return redirect("/")
    else:


        # get user stocks to populate form
        rows = cursor.execute("""
        SELECT symbol, shares FROM holdings
        WHERE user_id = ?
        """, (session["user_id"],)).fetchall()
        holdings = []
        for symbol, shares in rows:
            holdings.append({
                "symbol": symbol,
                "shares": shares
            })
            
        conn.close()
        
        return render_template("sell.html", holdings=holdings)

    
@app.route("/topup", methods=["GET", "POST"])
@login_required
def topup():
    conn = sqlite3.connect("finance.db")
    cursor = conn.cursor()
    
    if request.method == "POST":
        # get and validate cash amount
        amount = request.form.get("amount")
        if not amount:
            return apology("Must provide cash amount")

        try:
            amount = int(amount)
        except ValueError:
            return apology("Cash amount must be a positive integer")

        if amount < 1:
            return apology("Cash amount must be a positive integer")

        # update user cash
        cursor.execute("""
        UPDATE users
        SET cash = cash + ?
        WHERE id = ?;
        """, (amount, session["user_id"]))

        conn.commit()

        conn.close()
        
        return redirect("/")
    else:
        cash = cursor.execute("""
        SELECT cash FROM users
        WHERE id = ?;
        """, (session["user_id"],)).fetchone()[0]
        conn.close()
        return render_template("topup.html", cash=cash

)
