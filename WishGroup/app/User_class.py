from app import db
from flask.ext import login
from Member_class import Member

class User(db.Model, login.UserMixin):
	__tablename__ = 'user'
	id = db.Column(db.Integer, primary_key = True)
	username = db.Column(db.String(128), index = True, unique = True)
	password = db.Column(db.String(20))
	members = db.relationship('Member', backref = 'user', lazy = 'dynamic')

# ------------------------------------------------------------------------------
	def __init__(self, username, password):
		self.username = username
		self.password = password

	def __repr__(self):
		return '<User %r>' % (self.username)



# ==============================================================================

def find_user_by_id(user_id):
	return User.query.get(user_id)

def find_user_by_name(user_name):
	return User.query.filter(User.username == user_name).first()

def add_user(username, password):
	db.session.add(User(username, password))
	db.session.commit()

def check_user(username, password):
	result = find_user_by_name(username)
	return result and result.password == password

