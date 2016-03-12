# The base class for Wish Group Element.

class Base():
	id = db.Column(db.Integer, primary_key = True)
	timestamp = db.Column(db.DateTime)

	def __init__(self):
		self.timestamp = int(datetime.now().timestamp())

	def __repr__(self):
		return '<Base %r>' % (self.id)