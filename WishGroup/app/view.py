from flask import render_template, request, redirect, url_for, flash
from flask.ext import login
from app import app, login_manager
from .User_class import *
from .forms import RegistrationForm, LoginForm

@login_manager.user_loader
def load_user(user_id):
	return find_user_by_id(user_id)



# ----------------------------------------------------------

@app.route('/')
@app.route('/index')
def index():
	return render_template('index.html', current_user = login.current_user)


@app.route('/login', methods = ['GET', 'POST'])
def log_in():
	form = LoginForm(request.form)
	if request.method == 'POST' and form.validate():
		if check_user(form.username.data, form.password.data):
			login.login_user(find_user_by_name(form.username.data))
			flash('Success to Login.')
			print 'Success to Login.'
			print 'current username is ' + login.current_user.username
			return redirect(url_for('index'))

		else:
			flash('Fail to Login.')

	return render_template('login.html', \
		form = form, current_user = login.current_user)



@app.route('/logout')
@login.login_required
def log_out():
	login.logout_user()
	return redirect(url_for('index'))



@app.route('/register', methods = ['GET', 'POST'])
def register():
	form = RegistrationForm(request.form)

	print 'This is register...'

	if request.method == 'POST' and form.validate():

		print 'In!'

		if not find_user_by_name(form.username.data):
			add_user(form.username.data, form.password.data)
			flash('Thanks for registering')
			print 'return url_for(log_in).'
			return redirect(url_for('log_in'))

		else:
			print 'This username has already been used.'
			flash('This username has already been used.')

	print 'return register.html'
	return render_template('register.html', \
		form = form, current_user = login.current_user)



@app.errorhandler(404)
def not_found(error):
	print "Error %s: Can\'t not found this page." % (error)
	return render_template('404.html')


@app.route('/info')
@login.login_required
def user_info():
	return render_template('user_info.html', \
		current_user = login.current_user)
