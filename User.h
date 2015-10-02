#ifndef USER_H
#define USER_H

#include <string>

class User {
 public:
  User();
  User(std::string userName, std::string userPassword,
       std::string userEmail, std::string userPhone);
  std::string getName() const;
  void setName(std::string name);
  std::string getPassword() const;
  void setPassword(std::string password);
  std::string getEmail() const;
  void setEmail(std::string email);
  std::string getPhone() const;
  void setPhone(std::string phone);

 private:
  std::string name_;
  std::string password_;
  std::string email_;
  std::string phone_;
};

//一个用户的类
User::User()
{
    name_="web2014";
    password_="web2014";
    email_="web2014@163.com";
    phone_="10086";
}
User::User(std::string userName, std::string userPassword,
       std::string userEmail, std::string userPhone)
{
    name_=userName;
    password_=userPassword;
    email_=userEmail;
    phone_=userPhone;
}

std::string User::getName() const
{
    return name_;
}

void User::setName(std::string name)
{
    name_=name;
}

std::string User::getPassword() const
{
    return password_;
}

void User::setPassword(std::string password)
{
    password_=password;
}

std::string User::getEmail() const
{
    return email_;
}

void User::setEmail(std::string email)
{
    email_=email;
}

std::string User::getPhone() const
{
    return phone_;
}

void User::setPhone(std::string phone)
{
    phone_=phone;
}

#endif
