from app import db
from Member_class import Member
from Wish_class import Wish

wishgroup_member = db.Table('wishgroup_member',
	db.Column('member_id', db.Integer, db.ForeignKey('member.id')),
	db.Column('wishgroup_id', db.Integer, db.ForeignKey('wishgroup.id'))
	)

class Wishgroup(db.Model):
	__tablename__ = 'wishgroup'
	id = db.Column(db.Integer, primary_key = True)
	name = db.Column(db.String(120), index = True, unique = True)
	
	admin = db.Column(db.Integer, db.ForeignKey('member.id'))
	members = db.relationship('Member', secondary = wishgroup_member,
		backref = 'wishgroup')
	wishes = db.relationship('Wish', backref = 'wishgroup')

	def __repr__(self):
		return '<Group %r>' % (self.name)