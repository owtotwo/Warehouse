import sys; sys.path.append('../')

from config import NUM_OF_MEMBER_INIT_STARS
from app import db
from Wish_class import Wish

class Member(db.Model):
	__tablename__ = 'member'
	id = db.Column(db.Integer, primary_key = True)
	user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
	stars = db.Column(db.Integer)
	wishes = db.relationship('Wish', backref = 'wisher', lazy = 'dynamic', foreign_keys = 'Wish.wisher_id')
	tasks = db.relationship('Wish', backref = 'implementer', lazy = 'dynamic', foreign_keys = 'Wish.implementer_id')

# ------------------------------------------------------------------------------
'''
	def __init__(self, user_id, wishgroup_id):
		self.user_id = user_id
		self.wishgroup_id = wishgroup_id
		self.stars = NUM_OF_MEMBER_INIT_STARS

	def __repr__(self):
		return '<Wish %r>' % (self.body)


	def add_wish(self, body, stars):
		Wish.add_wish(body, stars, self.id, )

# ------------------------------------------------------------------------------

	def find_member(member_id):
		return Member.query.get(member_id)

	def add_member(user_id, group_id):
		creator = find_user_by_id(user_id)
		if creator.has_joined_group(group_id):
			print 'A member created by %s has already been created in this group.' % (creator.username)
			return False
		else:
			mem = Member(user_id, group_id)
			db.session.add(mem)
			db.session.commit()
			print '%s Success to add Member.' % (creator.username)
			return True

	def remove_member(member_id):
		mem = find_member(member_id)
		if mem:
			db.session.delete(mem)
			db.session.commit()
			return True
		else:
			return False
'''