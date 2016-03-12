#!../flask/bin/python
import sys
sys.path.append("../")    # add root folder"WishGroup" to the system path

from migrate.versioning import api
from config import SQLALCHEMY_DATABASE_URI
from config import SQLALCHEMY_MIGRATE_REPO

cur_ver = api.db_version(SQLALCHEMY_DATABASE_URI, SQLALCHEMY_MIGRATE_REPO)
api.downgrade(SQLALCHEMY_DATABASE_URI, SQLALCHEMY_MIGRATE_REPO, cur_ver - 1)
print 'Current database version: ' + str(api.db_version(
	SQLALCHEMY_DATABASE_URI, SQLALCHEMY_MIGRATE_REPO))