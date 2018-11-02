import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    # style 50 didn't like the '\' breaks that I'd added to wrap these lines of code

    if not request.form.get("firstname") or not request.form.get("lastname") or not request.form.get("address") or not request.form.get("age") or not request.form.get("gender") or not request.form.get("distance") or not request.form.get("overnight") or not request.form.get("drive"):
        return render_template("error.html", message="Please respond to all fields on the form.")
    file = open("survey.csv", "a")
    writer = csv.writer(file)
    writer.writerow((request.form.get("firstname"), request.form.get("lastname"), request.form.get("address"), request.form.get(
        "age"), request.form.get("gender"), request.form.get("distance"), request.form.get("overnight"), request.form.get("drive")))
    file.close()
    return redirect("/sheet")

# code from Week 7 lecture, customized to suit my needs
# csv.reader returns a list of many lists (i.e. rows)


@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open("survey.csv", "r") as file:
        reader = csv.reader(file)
        hikers = list(reader)
        file.close()
    return render_template("sheet.html", hikers=hikers)
