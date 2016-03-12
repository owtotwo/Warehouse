from app import db

class User(db.Model):
	__tablename__ = 'user'
	id = db.Column(db.Integer, primary_key = True)
	username = db.Column(db.String(128), index = True, unique = True)
	password = db.Column(db.String(20))
	members = db.relationship('Member', backref = 'user')

# ------------------------------------------------------------------------------

	def __init__(self, username, password):
		self.username = username
		self.password = password

	def __repr__(self):
		return '<User %r>' % (self.username)

'''
from sqlalchemy import text
from Member_class import Member
from Group_class import Group

	def get_id(self):
		return unicode(self.id)

	def join_group_by_id(self, group_id):
		Member.add_member(self.id, group_id)

	def join_group_by_name(self, group_name):
		Member.add_member(self.id, Group.find_group_by_name(group_name).id)

	def has_joined_group(self, group_id):
		return group_id in [i.group_id for i in self.members]


# ------------------------------------------------------------------------------

	def find_user_by_id(user_id):
		return User.query.get(user_id);

	def find_user_by_name():
		lis = User.query.from_statement(
			text('select * from user where username = \"%s\"' % (uname))).all()
		if lis:
			return lis[0]
		else:
			return None

	def add_user(uname, pwd):
		u = User(username = uname, password = pwd)
		if find_user_by_name(u.username):
			print 'User %s is already Signed up.' % (u.username)
			return False
		else:
			db.session.add(u)
			db.session.commit()
			print 'Success to add User %s.' % (u.username)
			return True

	def remove_user(uname):	
		u = find_user_by_name(uname)
		if u:
			db.session.delete(u)
			db.session.commit()
			return True
		else:
			print 'No this User'
			return False

'''