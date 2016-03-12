#!../flask/bin/python

import sys; sys.path.append('../')
from config import DB_ADDRESS
from sqlite3 import *

conn = connect(DB_ADDRESS) # link database
print 'Success to Connect...'

cur = conn.cursor() # create cursor instance
ex = cur.execute # for convenience

ex("pragma foreign_keys = on;") # open the foreign key constraints

ex("create table user(\
		id integer primary key autoincrement,\
		username string unique,\
		password string\
	);")

ex("create table member(\
		id integer primary key autoincrement,\
		name string references user(username) \
			on update cascade on delete cascade,\
		stars integer check(stars >= 0)\
	);")

conn.close()
