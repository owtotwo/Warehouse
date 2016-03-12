from flask.ext.wtf import Form
from wtforms import Form, BooleanField, TextField, PasswordField, validators, StringField

class LoginForm(Form):
	username = StringField('username', validators = [validators.DataRequired()])
	password = PasswordField('password', validators = [validators.DataRequired()])


class RegistrationForm(Form):
    username = TextField('Username', [validators.Length(min = 4, max = 40)])
    password = PasswordField('New Password', [
        validators.Required(),
        validators.Length(min = 6, max = 20),
        validators.EqualTo('confirm', message='Passwords must match')
    ])
    confirm = PasswordField('Repeat Password')