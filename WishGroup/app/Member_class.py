import sys; sys.path.append('../')

from config import NUM_OF_MEMBER_INIT_STARS
from app import db
from Wish_class import Wish

class Member(db.Model):
	__tablename__ = 'member'

	id = db.Column(db.Integer, primary_key = True)
	stars = db.Column(db.Integer)

	user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
	wishgroup_id = db.Column(db.Integer, db.ForeignKey('wishgroup.id'))

	wishes = db.relationship('Wish', backref = 'wisher', lazy = 'dynamic', foreign_keys = 'Wish.wisher_id')
	tasks = db.relationship('Wish', backref = 'implementer', lazy = 'dynamic', foreign_keys = 'Wish.implementer_id')

# ------------------------------------------------------------------------------

	def __init__(self, user_id, wishgroup_id):
		self.stars = NUM_OF_MEMBER_INIT_STARS
		self.user_id = user_id
		self.wishgroup_id = wishgroup_id

	def __repr__(self):
		return '<Member %r>' % (self.id)


# ==============================================================================

def find_member_by_id(member_id):
	pass



