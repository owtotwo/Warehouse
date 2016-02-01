#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
 public:
  Date();
  Date(int y, int m, int d, int h, int mi);
  int getYear(void) const;
  void setYear(int year);
  int getMonth(void) const;
  void setMonth(int month);
  int getDay(void) const;
  void setDay(int day);
  int getHour(void) const;
  void setHour(int hour);
  int getMinute(void) const;
  void setMinute(int minute);
  static bool isValid(Date date);
  static Date stringToDate(std::string dateString);
  static std::string dateToString(Date date);
  Date &operator=(const Date& date);
  bool operator==(const Date& date) const;
  bool operator>(const Date& date) const;
  bool operator<(const Date& date) const;
  bool operator>=(const Date& date) const;
  bool operator<=(const Date& date) const;

 private:
  int year_;
  int month_;
  int day_;
  int hour_;
  int minute_;
};

Date::Date()
{
    year_=1997;
    month_=5;
    day_=7;
    hour_=8;
    minute_=0;
}

Date::Date(int y, int m, int d, int h, int mi)
{
    year_=y;
    month_=m;
    day_=d;
    hour_=h;
    minute_=mi;
}

int Date::getYear(void) const
{
    return year_;
}

void Date::setYear(int year)
{
    year_=year;
}

int Date::getMonth(void) const
{
    return month_;
}

void Date::setMonth(int month)
{
    month_=month;
}

int Date::getDay(void) const
{
    return day_;
}

void Date::setDay(int day)
{
    day_=day;
}

int Date::getHour(void) const
{
    return hour_;
}

void Date::setHour(int hour)
{
    hour_=hour;
}

int Date::getMinute(void) const
{
    return minute_;
}

void Date::setMinute(int minute)
{
    minute_=minute;
}

bool Date::isValid(Date date)
{
    if(date.month_>12 || date.month_<1)
        return false;
    if(date.month_==4 ||
       date.month_==6 ||
       date.month_==9 ||
       date.month_==11)
    {
        if(date.day_>30)
            return false;
    }
    if(date.day_>31)
    {
        return false;
    }
    if(date.month_==2)
    {
        //特殊月份
        if(date.year_/4==0 && date.day_>29)
        {
            //闰年
            return false;
        }
        if(date.year_/4!=0 && date.day_>28)
        {
            //非闰年
            return false;
        }
    }
    if(date.hour_>23 || date.hour_<0)
        return false;
    if(date.minute_>59 || date.minute_<0)
        return false;
    return true;
}


Date Date::stringToDate(std::string dateString){
    //字符串形式的日期转为Date形式"2014-06-07/12:00"
    char* pt=new char[dateString.size()+1];
    int year=0,month=0,day=0,hour=0,minute=0;
    year=pt[0]*1000+pt[1]*100+pt[2]*10+pt[3];
    month=pt[5]*10+pt[6];
    day=pt[8]*10+pt[9];
    hour=pt[11]*10+pt[12];
    minute=pt[14]*10+pt[15];
    return Date(year,month,day,hour,minute);
}

std::string Date::dateToString(Date date)
{
    std::string trans(int n);
    int year=0,month=0,day=0,hour=0,minute=0;
    std::string save;
    year=date.getYear();
    month=date.getMonth();
    day=date.getDay();
    hour=date.getHour();
    minute=date.getMinute();
    save+=trans(year);
    save+="-";
    save+=trans(month);
    save+="-";
    save+=trans(day);
    save+="/";
    save+=trans(hour);
    save+=":";
    save+=trans(minute);
    //int转换string
    return save;
}

std::string trans(int n)
{
    std::string st;
    if(n<0)
        return '\0';
    if(n>99)
    {
        st+=(char)('0'+n/1000);
        st+=(char)('0'+n/100-(n/1000)*10);
    }
    st+=(char)('0'+n/10-(n/100)*10);
    st+=(char)('0'+n-(n/10)*10);
    return st;
}

Date& Date::operator=(const Date& date){
    year_=date.getYear();
    month_=date.getMonth();
    day_=date.getDay();
    hour_=date.getHour();
    minute_=date.getMinute();
    return (*this);
}

bool Date::operator==(const Date& date) const{
    if(year_==date.getYear() &&
       month_==date.getMonth() &&
       day_==date.getDay() &&
       hour_==date.getHour() &&
       minute_==date.getMinute())
        return true;
    else
        return false;
}

bool Date::operator>(const Date& date) const{
    if(year_>date.getYear())
        return true;
    else if(year_<date.getYear())
        return false;
    else{
        if(month_>date.getMonth())
            return true;
        else if(month_<date.getMonth())
            return false;
        else{
            if(day_>date.getDay())
                return true;
            else if(day_<date.getDay())
                return false;
            else{
                if(hour_>date.getHour())
                    return true;
                else if(hour_<date.getHour())
                    return false;
                else{
                    if(minute_>date.getMinute())
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}

bool Date::operator<(const Date& date) const{
    return (!(date==(*this) || (*this)>date));
}

bool Date::operator>=(const Date& date) const{
    return !((*this)<date);
}

bool Date::operator<=(const Date& date) const{
    return !((*this)>date);
}

#endif
