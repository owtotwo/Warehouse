echo Cleaning...
touch app/hey.pyc
touch hey.pyc
rm *.pyc
find ./app/ -name *.pyc | xargs rm
echo done!
clear 
