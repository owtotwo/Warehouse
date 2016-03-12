import os
basedir = os.path.abspath(os.path.dirname(__file__))

# address of saving database
DATABASE_NAME = 'app.db'
DATABASE_ADDRESS = os.path.join(basedir, 'db', DATABASE_NAME)

print 'I am in config.py'
print DATABASE_ADDRESS

# init value of classes
NUM_OF_MEMBER_INIT_STARS = 5
