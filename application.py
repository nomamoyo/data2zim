import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("Sorry Noma got really tired! #noextensions #longweeek")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # if user reached route via GET, render searching form
    if request.method == "GET":
        return render_template("buy.html")

    # if user reached route via POST by submitting a completed quote form, store user id and check input
    else:
        if not request.form.get("symbol"):
            return apology("Symbol missing")

        elif not request.form.get("shares"):
            return apology("Enter number of shares")

        # if number of shares is negative or not a whole #, prompt user for positive value
        # checking method inspired by Quora :) https://www.quora.com/How-do-you-check-if-a-number-is-a-float-in-Python
        value = request.form.get("shares")
        if not isinstance(value, int) and int(value) < 0:
            return apology("Provide a positive integer")

        # otherwise, just convert value into integer. I did this after running into an error with my cost calculation later on
        value = int(value)

        # lookup quote - based on helpers, lookup returns a dictionary of three value-key pairs
        quote = lookup(request.form.get("symbol"))

        # if quote is not found
        if not quote:
            return apology("Stock not found")

        # if quote is found, calculate cost of shares that user wants to buy
        cost = float(quote["price"] * value)

        # SELECT cash based on user id
        balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # extract cash value following the same convention that login uses to extract the user id
        curr_bal = balance[0]['cash']

        # calculate whether user can afford shares or not
        if curr_bal < cost:
            return apology("You have insufficient funds.")

        # casting shares value into integer because for some reason it was coming through as a string
        shares2 = int(request.form.get("shares"))

        # insert transaction into history table
        db.execute("INSERT INTO history (id, symbol, price, shares, tot_cost) VALUES (:id, :symbol, :price, :shares, :tot_cost)",
                   id=session["user_id"], symbol=quote["symbol"], price=quote["price"], shares=shares2, tot_cost=cost)

        # update cash based on curr_balance - cost
        # new_bal = curr_bal - cost

        # update users table based on https://www.w3schools.com/sql/sql_update.asp
        # the subtraction inspired by discourse
        update = db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id", id=session["user_id"], cost=cost)

        # got to main page
        return render_template("index.html")

        # if there was an error updating the database
        if not update:
            return apology("Database update error")


@app.route("/check", methods=["GET"])
def check():
    # code based on lecture source code
    # Query database for username, output is a list
    users = db.execute("SELECT * FROM users WHERE username = :username", username=request.args.get("username"))

    # if username not found i.e. lenght of users = 0, and length of actual username is greater then 0 return true, otherwise false
    if len(users) == 0 and len(request.args.get("username")) > 0:
        return jsonify(True)
    else:
        return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("Sorry Noma got really tired! #noextensions #longweek")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    # if user reached route via GET, render searching form
    if request.method == "GET":
        return render_template("quote.html")

    else:
        # if user reached route via POST by submitting a completed quote form, check input
        if not request.form.get("symbol"):
            return apology("Symbol missing")

        # lookup quote - based on helpers, lookup returns a dictionary of three value-key pairs
        quote = lookup(request.form.get("symbol"))

        # if quote is found
        if quote:
            # render quoted and extract the three values, wrap the price in helper function usd
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=usd(quote["price"]))

        # if not found
        return apology("Stock not found")


@app.route("/register", methods=["GET", "POST"])
def register():

    # if user reached route via GET, render registration form
    if request.method == "GET":
        return render_template("register.html")

    # if user reached route via POST by submitting a completed registration form, check inputs
    else:
        if not request.form.get("username"):
            return apology("Missing username")

        elif not request.form.get("password"):
            return apology("Missing password")

        elif not request.form.get("confirmation"):
            return apology("Retype your password")

        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords don't match")

        # hash the password
        hashed = generate_password_hash(request.form.get("password"))

        # insert new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashed)",
                   username=request.form.get("username"), hashed=hashed)

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        # remember user
        session["user_id"] = rows[0]["id"]

        # redirect user to homepage
        return render_template("index.html")

        # if something goes wrong in inserting the user into the database, throw db error - try again later
        if not rows:
            return apology("Database error")
            # return user to registration page
            return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("Sorry Noma got really tired! #noextensions #longweeek")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
