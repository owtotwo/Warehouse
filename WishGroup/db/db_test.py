#!../flask/bin/python
import sys; sys.path.append('../')
from app import models, db
from flask.ext.sqlalchemy import SQLAlchemy



#db.session.add(models.Wishgroup(name = 'Jump'))
#print 'Group over!'
#db.session.add(models.Member(stars = 10))
#print 'Member over!'
'''
db.session.add(models.User('Tom', '123'))
db.session.add(models.User('owtotwo', '123'))
print models.User.query.all()
print '---------update owtotwo-------'
db.session.add(models.Wish('I hope today is Saturday!', 2, 1))
db.session.add(models.Wish('I hope today is Sunday!', 1, 2))
u = models.User.query.get(4)
u.password = '12380250'
db.session.add(u)
'''
for i in models.User.query.all():
	print i.id, i.username, i.password
print models.Wishgroup.query.all()
print models.Member.query.all()

db.session.commit()
