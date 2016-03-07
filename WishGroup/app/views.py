from app import app
from flask import render_template

@app.route('/')
@app.route('/index')
def index():
	name = "owtotwo"
	return render_template("index.html", name = name)
