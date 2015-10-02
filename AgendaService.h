#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include "Storage.h"
#include <list>
#include <string>

class AgendaService {
 public:
  AgendaService();
  ~AgendaService();
  bool userLogIn(std::string userName, std::string password);
  bool userRegister(std::string userName, std::string password,
                    std::string email, std::string phone);
  bool deleteUser(std::string userName, std::string password);
	// a user can only delete itself
  std::list<User> listAllUsers(void);

  bool createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate);
  std::list<Meeting> meetingQuery(std::string userName, std::string title);
  std::list<Meeting> meetingQuery(std::string userName, std::string startDate,
                                  std::string endDate);
  std::list<Meeting> listAllMeetings(std::string userName);
  std::list<Meeting> listAllSponsorMeetings(std::string userName);
  std::list<Meeting> listAllParticipateMeetings(std::string userName);
  bool deleteMeeting(std::string userName, std::string title);
  bool deleteAllMeetings(std::string userName);

  void startAgenda(void);
  void quitAgenda(void);

 private:
  Storage *storage_;
};

//auto myfunc=[](User& pt){return Date::isVaild(pt.)};



AgendaService::AgendaService(){
    storage_=Storage::getInstance();
}

AgendaService::~AgendaService(){
    storage_->~Storage();
}

bool AgendaService::userLogIn(std::string userName,
                        std::string password){
    //判断与list中是否吻合
    std::list<User> lis;
    lis=storage_->queryUser([userName,password](const User& pt){return
       (userName==pt.getName() && password==pt.getPassword());});
    if(lis.size()==0){
        return false;
    }
    return true;
}

bool AgendaService::userRegister(std::string userName,
    std::string password, std::string email, std::string phone){
    if(userName.length()==0 ||
       password.length()==0 ||
       email.length()==0 ||
       phone.length()==0)
        return false;                       //·ÀÖ¹Îª¿Õ
    storage_->createUser(User(userName,password,email,phone));
    return true;
}

bool AgendaService::deleteUser(std::string userName,
                    std::string password){
    return true;
}
	// a user can only delete itself


std::list<User> AgendaService::listAllUsers(void){
    return storage_->queryUser(
        [](const User& pt){return true;} );
}


bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate){
    if(startDate>endDate)
        return false;
    storage_->createMeeting( Meeting(userName,participator,
                Date::stringToDate(startDate),Date::stringToDate(endDate),title) );
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                        std::string title){
    return storage_->queryMeeting( [userName,title](const Meeting& pt)
                {return (userName==pt.getSponsor() || userName==pt.getParticipator())
                 && title==pt.getTitle();} );
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                std::string startDate, std::string endDate){
    return storage_->queryMeeting([userName,startDate,endDate](const Meeting& pt){return (
    userName==pt.getSponsor() && startDate==Date::dateToString(pt.getStartDate())
    && endDate==Date::dateToString(pt.getEndDate()));});
}


std::list<Meeting> AgendaService::listAllMeetings(std::string userName){
    return storage_->queryMeeting([userName](const Meeting& pt){return
                            (userName==pt.getSponsor() || userName==pt.getParticipator());});
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName){
    return storage_->queryMeeting([userName](const Meeting& pt)
                                  {return userName==pt.getSponsor();});
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName){
    return storage_->queryMeeting([userName](const Meeting& pt)
                                  {return userName==pt.getParticipator();});
}

bool AgendaService::deleteMeeting(std::string userName, std::string title){
    return storage_->deleteMeeting([userName,title](const Meeting& pt)
                            {return (userName==pt.getSponsor() && title==pt.getTitle());});
}

bool AgendaService::deleteAllMeetings(std::string userName){
    return storage_->deleteMeeting([userName](const Meeting& pt)
                            {return userName==pt.getSponsor();});
}

void AgendaService::startAgenda(void){
    storage_->sync();
}
void AgendaService::quitAgenda(void){
    storage_->~Storage();
}

#endif
