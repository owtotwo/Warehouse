#!../flask/bin/python
import sys; sys.path.append('../')
from app import models, db
from flask.ext.sqlalchemy import SQLAlchemy

User = models.User
Member = models.Member
Wishgroup = models.Wishgroup
Wish = models.Wish



db.session.add(User('Tom', '123'))
db.session.add(User('owtotwo', '123'))
db.session.add(User('Jack', '123456'))
db.session.add(User('TEST_USER', '1008611'))

db.session.add(Wishgroup(name = 'MSTC'))
db.session.add(Wishgroup(name = 'Jump'))
print 'Group over!'

db.session.add(Member(1, 1))
print 'Member over!'

db.session.add(Wish('I hope today is Saturday!', 2))
db.session.add(Wish('I hope today is Sunday!', 1))


'''
mem = Member()
db.session.add()
'''
print '\nUser : '
for i in models.User.query.all():
	print i.id, i.username, i.password

print '\nWishgroup : '
print models.Wishgroup.query.all()

print '\nMember : '
print models.Member.query.all()

print '\nWish : '
print models.Wish.query.all()

db.session.commit()
