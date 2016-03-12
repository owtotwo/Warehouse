from flask import render_template, request, redirect, url_for
from flask.ext import login
from app import app
from app import login_manager
import user


@login_manager.user_loader
def load_user(user_id):
	return user.find_user_by_id(user_id)



# ----------------------------------------------------------

@app.route('/')
@app.route('/index')
def index():
	return 'Hello flask login app!'

@app.route('/login', methods = ['GET', 'POST'])
def log_in():
	if request.method == 'POST':
		username = request.form.get('username')
		password = request.form.get('password')
		print 'username = ' + str(type(username))
		print 'password = ' + str(type(password))
		if user.is_valid_user(username, password):
			login.login_user(user.get_user(username))
			print 'Success to Login.'
			print 'current username is ' + login.current_user.username
			return 'Congratuations!'
		else:
			return 'Sorry!'
	else:
		return render_template('login.html')

@app.route('/logout')
@login.login_required
def log_out():
	login.logout_user()
	print 'I am in logout().'
	return redirect(url_for('index'))

@app.route('/info')
@login.login_required
def user_info():
	return render_template('user_info.html', current_user = login.current_user)
