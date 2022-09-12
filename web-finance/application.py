import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    money = usd(db.execute("SELECT cash FROM users WHERE id=(?)", session["user_id"])[0]["cash"])
    table = db.execute("SELECT symbol, name, SUM(shares) AS shares, price, SUM(total) AS total FROM 'table' WHERE user_id=(:iden) GROUP BY name", iden=session["user_id"])
    for row in table:
        row["price"] = usd(row["price"])
        row["total"] = usd(row["total"])
    return render_template("index.html", money=money, table=table)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide a Symbol")

        elif lookup(request.form.get("symbol")) == None:
            return apology("Symbol do not exist")

        if not request.form.get("shares"):
            return apology("Must provide Qty.")


        if int(request.form.get("shares")) < 1:
            return apology("Invalid qty")

        money = db.execute("SELECT cash FROM users WHERE id=(?)", session["user_id"])[0]

        money = money["cash"]
        print(money)

        a = float(lookup(request.form.get("symbol"))["price"])
        m = float(request.form.get("shares"))
        n = m*a
        result = money - n
        now = datetime.now()
        trans = now.strftime("%d-%m-%Y %H:%M:%S")
        if result >= 0:
            db.execute("UPDATE users SET cash=(:cash) WHERE id=(:ident)", cash=result, ident=session["user_id"])

            name = lookup(request.form.get("symbol"))["name"]
            symbol = lookup(request.form.get("symbol"))["symbol"]

            db.execute("INSERT INTO 'table' (user_id, symbol, name, shares, price, total, transacted) VALUES (?,?,?,?,?,?,?)",
            session["user_id"], symbol, name, m, a, n, trans)


            return redirect("/")
        else:
            return apology("Dont have enough money")

        redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    table = db.execute("SELECT symbol, shares, price, transacted FROM 'table' WHERE user_id=(:iden)", iden=session["user_id"])
    for row in table:
        row["price"] = usd(row["price"])
    return render_template("history.html", table=table)



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

    if request.method == "POST":
        name = lookup(request.form.get("symbol"))["name"]
        price = usd(lookup(request.form.get("symbol"))["price"])
        symbol = lookup(request.form.get("symbol"))["symbol"]

        return render_template("quoted.html", name=name, price=price, symbol=symbol)
    else:
        return render_template("quote.html")
    #if request.method == "GET":

    #return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():

    name = request.form.get("username")
    word = request.form.get("password")
    word2 = request.form.get("password2")

    if request.method == "GET":
        return render_template("register.html")
    else:

        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("password2"):
            return apology("must repeat password", 403)

        for i in db.execute("SELECT username FROM users WHERE 1"):
            if name == (i["username"]):
                 return apology("Sorry, the username is already taken")


        if request.form.get("password") != request.form.get("password2"):
            return apology("Passwords didnt match.")

        else:

            db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=name, password=generate_password_hash(word))

            return redirect("/")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        #ver se tem as acoes
        number = -int(request.form.get("number")) #shares to sell
        name = request.form.get("opt")
        if request.form.get("opt") == "Symbol":
            return apology("You need to select one share to sell")


        #check if the user have this much of shares
        if number > int(db.execute("SELECT SUM(shares) AS shares FROM 'table' WHERE user_id=(?) AND name=(?)", session["user_id"], name)[0]["shares"]):
            return apology("You dont have that much to sell")

        #sell
        money = db.execute("SELECT cash FROM users WHERE id=(?)", session["user_id"])[0]
        money = money["cash"]
        symbol = db.execute("SELECT symbol FROM 'table' WHERE name=(?)", name)[0]["symbol"]
        price = float(lookup(symbol)["price"])
        n = number*price
        result = money - n
        now = datetime.now()
        trans = now.strftime("%d-%m-%Y %H:%M:%S")

        db.execute("UPDATE users SET cash=(:cash) WHERE id=(:ident)", cash=result, ident=session["user_id"])


        db.execute("INSERT INTO 'table' (user_id, symbol, name, shares, price, total, transacted) VALUES (?,?,?,?,?,?, ?)",
        session["user_id"], symbol, name, number, price, n, trans)



        return redirect("/")
    else:



        actions = db.execute("SELECT name FROM 'table' WHERE user_id=? GROUP BY name", session["user_id"])
        return render_template("sell.html", actions=actions)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
