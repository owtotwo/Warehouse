from app import app
from flask import render_template, flash, redirect
from .forms import LoginForm

@app.route('/')
@app.route('/index')
def index():
	user = { 'nickname': 'owtotwo' }
	posts = [
		{'author': {'nickname': 'Tom'}, 'body': 'The Avengers movie was so cool! '},
		{'author': {'nickname': 'Jack'}, 'body': 'I don\'t think so. '}
	]
	return render_template('index.html', user = user, posts = posts)

@app.route('/login', methods = ['GET', 'POST'])
def login():
	form = LoginForm()
	if form.validate_on_submit():
		flash('login requested for OpenID=\"' + form.openid.data
			+ '\", remember_me = ' + str(form.remember_me.data))
		return redirect('/index')
	return render_template('login.html', 
		title = 'Sign In',
		form = form)
