from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET",  "POST"])
def index():
    name = request.form.get("name", "world")
    return render_template("index.html", name=name)
