import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    user_id = session["user_id"]

    cash = db.execute("SELECT * FROM users WHERE id = ?;", user_id)[0]["cash"]
    rows = db.execute("SELECT *, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol;", user_id)

    total = cash
    for row in rows:
        total += row["price"] * row["total_shares"]

    return render_template("index.html", rows=rows, cash=cash, total=total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    user_id = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()

        # ensure stock symbol input
        if not symbol:
            return apology("please enter a stock symbol!")

        stock = lookup(symbol)

        # ensure stock is found
        if not stock:
            return apology("invalid stock symbol!")

        # ensure valid number of shares
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("number of shares must be an integer")
        if shares <= 0:
            return apology("number of shares must be at least 1!")

        cash = db.execute("SELECT cash FROM users WHERE id = ?;", user_id)[0]["cash"]
        name = stock["name"]
        price = stock["price"]
        total_price = price * shares

        # check if user has enough cash
        if cash < total_price:
            return apology("not enough cash!")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash - total_price, user_id)
            db.execute("INSERT INTO transactions (user_id,name,shares,price,type,symbol) VALUES (?,?,?,?,?,?);",
                       user_id, name, shares, price, "BUY", symbol)

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?;", user_id)

    return render_template("history.html", transactions=transactions, usd=usd)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()

        # ensure stock symbol input
        if not symbol:
            return apology("please enter a stock symbol!")

        # ensure stock is found
        stock = lookup(symbol)

        if not stock:
            return apology("invalid stock symbol!")

        price = usd(stock["price"])

        # renders page with stock information
        return render_template("quoted.html", stock=stock, price=price)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # ensure password cofirmation
        elif password != confirmation:
            return apology("passwords must match", 400)

        # ensure username is unique
        elif db.execute("SELECT * FROM users WHERE username = ?;", username):
            return apology("username is already taken", 400)

        # hash password
        hashed_password = generate_password_hash(password)

        # register username and hash to the database
        db.execute("INSERT INTO users (username,hash) VALUES (?,?);", username, hashed_password)

        # Remember which user has logged in
        rows = db.execute("SELECT * FROM users WHERE username = ?;", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # ensure stock is selected
        if not symbol:
            return apology("please select a stock!")

        # ensure user owns selected stock
        if not db.execute("SELECT * FROM transactions WHERE user_id = ? AND symbol = ?;", user_id, symbol):
            return apology("user does not own any shares of selected stock!")

        # ensure input is a positive integer
        if int(shares) < 1:
            return apology("number of shares must be a positive integer!")

        # ensure user owns enough stock
        user_shares = db.execute("SELECT *, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol;",
                                 user_id, symbol)[0]["total_shares"]
        if user_shares < int(shares):
            return apology("user does not own enough shares of selected stock!")

        cash = db.execute("SELECT cash FROM users WHERE id = ?;", user_id)[0]["cash"]
        name = lookup(symbol)["name"]
        price = lookup(symbol)["price"]
        total_price = price*int(shares)

        db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash + total_price, user_id)
        db.execute("INSERT INTO transactions (user_id,name,shares,price,type,symbol) VALUES (?,?,?,?,?,?);",
                   user_id, name, -int(shares), price, "SELL", symbol)

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?;", user_id)
        return render_template("sell.html", symbols=symbols)