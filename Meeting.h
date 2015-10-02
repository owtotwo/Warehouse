#ifndef MEETING_H
#define MEETING_H

#include "Date.h"

class Meeting {
 public:
  Meeting();
  Meeting(std::string sponsor, std::string participator,
          Date startTime, Date endTime, std::string title);
  std::string getSponsor(void) const;
  void setSponsor(std::string sponsor);
  std::string getParticipator(void) const;
  void setParticipator(std::string participator);
  Date getStartDate(void) const;
  void setStartDate(Date startTime);
  Date getEndDate(void) const;
  void setEndDate(Date endTime);
  std::string getTitle(void) const;
  void setTitle(std::string title);

 private:
  std::string sponsor_;
  std::string participator_;
  Date startDate_;
  Date endDate_;
  std::string title_;
};

Meeting::Meeting(){
    sponsor_="中山大学";
    participator_="中大学生";
    startDate_=Date(2000,1,1,0,0);
    endDate_=Date(2000,1,1,0,0);
    title_="爱你的中大";
}

Meeting::Meeting(std::string sponsor, std::string participator,
          Date startTime, Date endTime, std::string title){
    sponsor_=sponsor;
    participator_=participator;
    startDate_=startTime;
    endDate_=endTime;
    title_=title;
}

std::string Meeting::getSponsor(void) const{
    return sponsor_;
}

void Meeting::setSponsor(std::string sponsor){
    sponsor_=sponsor;
}

std::string Meeting::getParticipator(void) const{
    return participator_;
}

void Meeting::setParticipator(std::string participator){
    participator_=participator_;
}

Date Meeting::getStartDate(void) const{
    return startDate_;
}
void Meeting::setStartDate(Date startTime){
    startDate_=startTime;
}

Date Meeting::getEndDate(void) const{
    return endDate_;
}

void Meeting::setEndDate(Date endTime){
    endDate_=endTime;
}
std::string Meeting::getTitle(void) const{
    return title_;
}

void Meeting::setTitle(std::string title){
    title_=title;
}

#endif
