import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd



# Configure application
app = Flask(__name__)
app.jinja_env.filters["usd"] = usd

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.template_filter("to_decimal")
def to_decimal_filter(f):
    return decimal.Decimal(f)

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    mny = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    my_money = usd(mny[0]["cash"])
    my_mon = mny[0]["cash"]

    data = db.execute("SELECT symbol, SUM(CASE WHEN type = 'buy' THEN shares ELSE -shares END) AS shares FROM history WHERE user_id = ? GROUP BY symbol  HAVING shares > 0;", session["user_id"])

    curr_prices = {stock["symbol"]: lookup(stock["symbol"])["price"] for stock in data}
    tot_value = sum(row["shares"] * curr_prices[row["symbol"]] for row in data)
    total_value = usd(float(my_mon) - tot_value)
    return render_template("index.html", data=data, curr_prices=curr_prices, my_money=my_money, total_value=total_value)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol",400)
        elif not request.form.get("shares"):
            return apology("must provide shares",400)
        elif not request.form.get("shares").isdigit():
            return apology("must provide a number",400)
        # elif request.form.get("shares").isdecimal():
        #     return apology("not decimal",400)
        # elif int(request.form.get("shares")) <= 0:
        #     return apology("must provide positive shares",400)
        else:
            stock = lookup(request.form.get("symbol"))
            if not stock:
                return apology("must input a valid symbol", 400)
            total = stock["price"] * request.form.get("shares")
            price = stock["price"]
            money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            if price > money[0]["cash"]:
                return apology("You don't have enough money", 400)
            else:
                result_money = money[0]["cash"]-price
                db.execute("INSERT INTO purchases (user_id, symbol, price, shares, total) VALUES(?, ?, ?, ?, ?);", session["user_id"], request.form.get("symbol"), price, request.form.get("shares"), total)
                db.execute("INSERT INTO history (user_id, symbol, shares, price, total, type, datetime) VALUES(?, ?, ?, ?, ?, ?, ?);", session["user_id"], request.form.get("symbol"), request.form.get("shares"), price, total, "buy", datetime.now())
                db.execute("UPDATE users SET cash=? WHERE id=?;", result_money, session["user_id"])
                return redirect ("/")
    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    mny = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    my_money = mny[0]["cash"]
    data = db.execute("SELECT * FROM history WHERE user_id = ?;", session["user_id"])

    return render_template("history.html", data=data, my_money=my_money)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "POST":
        if request.form.get("symbol") == "":
            return apology("must input a symbol", 400)
        quoted = lookup(request.form.get("symbol"))
        if not quoted:
            return apology("must input a valid symbol", 400)
        return render_template("quoted.html", quoted=quoted)
    if request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
        # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) == 1:
            return apology("already registered", 400)

        elif (password != confirmation):
            return apology("password has to be the same as confirmation", 400)

        else:
            hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?);", username, hash)

        # Redirect user to home page
        return redirect("/")

    # Redirect user to login form
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol",400)
        elif not request.form.get("shares"):
            return apology("must provide shares",400)
        elif float(request.form.get("shares")) < 0:
            return apology("must provide positive shares",400)
        enough = db.execute("SELECT SUM(shares) AS shares FROM purchases WHERE user_id=? AND symbol=?;", session["user_id"], request.form.get("symbol"))
        if len(enough) < 1:
            return apology("you don't have shares", 400)
        elif float(request.form.get("shares")) > enough[0]['shares']:
            return apology("you don't have enough shares", 400)
        else:
            stock = lookup(request.form.get("symbol"))
            total = stock["price"] * float(request.form.get("shares"))
            value = stock["price"]
            money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

            db.execute("INSERT INTO sell (user_id, symbol, price, shares, total) VALUES(?, ?, ?, ?, ?);", session["user_id"], request.form.get("symbol"), value, request.form.get("shares"), total)

            db.execute("INSERT INTO history (user_id, symbol, price, shares, total, type, datetime) VALUES(?, ?, ?, ?, ?, ?, ?);", session["user_id"], request.form.get("symbol"), value, request.form.get("shares"), total, "sell", datetime.now())

            result_money = money[0]["cash"]+value
            db.execute("UPDATE users SET cash=? WHERE id=?;", result_money, session["user_id"])
            return redirect ("/")
    return render_template("sell.html")

@app.route("/add", methods=["GET", "POST"])
def add():
    if request.method == "POST":
        more_cash = request.form.get("more_cash")
        mny = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        my_money = mny[0]["cash"]
        result_money = my_money + float(more_cash)
        db.execute("UPDATE users SET cash=? WHERE id=?;", result_money, session["user_id"])
        return redirect("/")
    return render_template("add.html")
