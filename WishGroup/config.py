import os
basedir = os.path.abspath(os.path.dirname(__file__))

# address of saving database
SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(basedir, 'db/app.db')
SQLALCHEMY_MIGRATE_REPO = os.path.join(basedir, 'db/db_repository')

CSRF_ENABLED = True
SECRET_KEY = 'mstc wish groups'

# init value of classes
NUM_OF_MEMBER_INIT_STARS = 5
