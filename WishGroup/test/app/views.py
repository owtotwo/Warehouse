from app import app
from flask import render_template, request, redirect, url_for, abort

# =========================================================

@app.route('/')
@app.route('/index')
def index():
	name = 'owtotwo'
	return render_template('index.html', name = name)


@app.route('/login', methods = ['GET', 'POST'])
def login():
	if request.method == 'POST':
		username = request.form.get('username')
		password = request.form.get('password')
		remember_me = request.form.get('remember_me')
		print 'username is ' + username
		print 'password is ' + password
		if remember_me:
			print 'remember_me on'
		else:
			print 'remember_me off'
		if find_user_by_name(username).password == password:
			print "Success to Login In!"
			return redirect(url_for('index'))
		else:
			return "Password is wrong."
	try:
		return render_template('login.html')
	except TemplateNotFound:
		abort(404)


@app.route('/register', methods = ['GET', 'POST'])
def register():
	if request.method == 'POST':
		username = request.form.get('username')
		password_1 = request.form.get('password_1')
		password_2 = request.form.get('password_2')
		
		if find_user_by_name(username):
			return "This Username has already been used.\n"
		else:
			add_user(username, password_1)
			return redirect(url_for('login'))
	return render_template('register.html')


@app.errorhandler(404)
def not_found(error):
	print "Error %s: Can\'t not found this page." % (error)
	return render_template('404.html')