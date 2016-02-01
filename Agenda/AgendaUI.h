#ifndef AGENDAUI_H
#define AGENDAUI_H

#include "AgendaService.h"
#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;


class AgendaUI {
 public:
  AgendaUI();
  void OperationLoop(void);

 private:
  // task functions
  void startAgenda(void);
  std::string getOperation();
  bool executeOperation(std::string op);
  void userLogIn(void);
  void userRegister(void);
  void quitAgenda(void);
  void userLogOut(void);
  void deleteUser(void);
  void listAllUsers(void);
  void createMeeting(void);
  void listAllMeetings(void);
  void listAllSponsorMeetings(void);
  void listAllParticipateMeetings(void);
  void queryMeetingByTitle(void);
  void queryMeetingByTimeInterval(void);
  void deleteMeetingByTitle(void);
  void deleteAllMeetings(void);
  void printMeetings(std::list<Meeting> meetings);
  // dates
  std::string userName_;
  std::string userPassword_;
  AgendaService agendaService_;


  //�Լ��ӵ�
  bool UserStatus(void);                    //�жϣ��ο�/��¼��״̬
};

AgendaUI::AgendaUI(){
    //���캯��
    cout<<"��������"<<endl;
}

bool AgendaUI::UserStatus(){
    std::list<User> alluser=agendaService_.listAllUsers();
    std::list<User>::iterator it=alluser.begin();
    while((*it).getName()!=userName_ && it!=alluser.end()){
        it++;
    }
    return it!=alluser.end();           //trueΪ�ѵ�¼״̬
}

void AgendaUI::OperationLoop(){
    startAgenda();
    while(1){
        if(executeOperation(getOperation()))
            continue;
        else
            break;
    }
    cout<<"��ֽ�ټ�"<<endl;
}

void AgendaUI::startAgenda(){
    std::cout<<"****************************************************";
    std::cout<<std::endl<<"      Welcome to use the Agenda.  ���� by AT     "
    <<std::endl;

    agendaService_.startAgenda();
}

void AgendaUI::userLogIn(){
    if(UserStatus()){
        std::cout<<"�ѵ�¼����ǳ��ٽ��е�¼������"<<std::endl;
        return;
    }
    std::cout<<"��LogIn��"<<std::endl;
    std::string userName;
    std::string Password;
    cout<<"Username:";
    while(1){
        getline(cin,userName);

        if(userName.size()==0){
            std::cout<<"It can not be empty!"<<std::endl;
            continue;
        }
        break;
    }
    cout<<"Password:";
    while(1){
        getline(cin,Password);
        if(Password.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }
    if(agendaService_.userLogIn(userName,Password)){
        userName_=userName;
        userPassword_=Password;
        cout<<"��¼�ɹ���"<<endl;
    }
}

void AgendaUI::quitAgenda(){
    agendaService_.quitAgenda();
    //exit(0);
}



std::string AgendaUI::getOperation(){
    cout<<"\t1.userLogIn\n"<<
    "\t2.userRegister\n"<<
    "\t3.quitAgenda\n"<<
    "\t4.userLogOut\n"<<
    "\t5.deleteUser\n"<<
    "\t6.listAllUsers\n"<<
    "\t7.createMeeting\n"<<
    "\t8.listAllMeetings\n"<<
    "\t9.listAllSponsorMeetings\n"<<
    "\t10.listAllParticipateMeetings\n"<<
    "\t11.queryMeetingByTitle\n"<<
    "\t12.queryMeetingByTimeInterval\n"<<
    "\t13.deleteMeetingByTitle\n"<<
    "\t14.deleteAllMeetings\n"<<
    "\t15.printMeetings"<<endl;
    cout<<"Please enter the No. of the operation:";
    std::string str;
    getline(cin,str);
    return str;
}

bool AgendaUI::executeOperation(std::string op){
    if(op=="userLogIn" || op=="1")
        userLogIn();
    else if(op=="userRegister" || op=="2")
        userRegister();
    else if(op=="userLogOut" || op=="4")
        userLogOut();
    else if(op=="deleteUser" || op=="5")
        deleteUser();
    else if(op=="listAllUsers" || op=="6")
        listAllUsers();
    else if(op=="createMeeting" || op=="7")
        createMeeting();
    else if(op=="listAllMeetings" || op=="8")
        listAllMeetings();
    else if(op=="listAllSponsorMeetings" || op=="9")
        listAllSponsorMeetings();
    else if(op=="listAllParticipateMeetings" || op=="10")
        listAllParticipateMeetings();
    else if(op=="queryMeetingByTitle" || op=="11")
        queryMeetingByTitle();
    else if(op=="queryMeetingByTimeInterval" || op=="12")
        queryMeetingByTimeInterval();
    else if(op=="deleteMeetingByTitle" || op=="13")
        deleteMeetingByTitle();
    else if(op=="deleteAllMeetings" || op=="14")
        deleteAllMeetings();
    else if(op=="printMeetings" || op=="15")
        printMeetings(agendaService_.listAllMeetings(userName_));
    else if(op=="quitAgenda" || op=="3"){
        quitAgenda();
        return false;
    }
    else{
        cout<<"Please enter the correct operation."<<endl;
        return true;
    }
    return true;
}



void AgendaUI::userRegister(void){
    if(UserStatus()){
        cout<<"�ѵ�¼����ǳ��ٽ���ע�������"<<endl;
        return;
    }
    cout<<"��Register��"<<endl;
    std::string name,password,email,phone;
    std::string passwordagain;

    while(1){
        cout<<"UserName:";
        while(1){
            getline(cin,name);
            if(name.size()==0){
                cout<<"It can not be empty!"<<endl;
                continue;
            }
            break;
        }
        cout<<"Password:";
        while(1){
            getline(cin,password);
            if(password.size()==0){
                cout<<"It can not be empty!"<<endl;
                continue;
            }
            break;
        }
        cout<<"Email:";
        while(1){
            getline(cin,email);
            if(email.size()==0){
                cout<<"It can not be empty!"<<endl;
                continue;
            }
            break;
        }
        cout<<"Phone:";
        while(1){
            getline(cin,phone);
            if(phone.size()==0){
                cout<<"It can not be empty!"<<endl;
                continue;
            }
            break;
        }
        cout<<endl;
        cout<<"���ٴ���������:";
        getline(cin,passwordagain);
        if(passwordagain!=password){
            cout<<"�������벻һ�£�"<<endl;
            continue;
        }
        break;
    }

    if(agendaService_.userRegister(name,password,email,phone)){
        cout<<"ע��ɹ���"<<endl;
        return;
    }
    cout<<"ע��ʧ��"<<endl;
}

void AgendaUI::printMeetings(std::list<Meeting> meetings){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    cout<<"����������"<<endl;
    std::list<Meeting>::iterator it=meetings.begin();
    for(;it!=meetings.end();it++){
        cout<<"���⣺"<<(*it).getTitle()<<" ";
        cout<<"�����ߣ�"<<(*it).getSponsor()<<" ";
        cout<<"������"<<(*it).getParticipator()<<endl;
    }
    cout<<"������"<<endl;
}

void AgendaUI::userLogOut(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    userName_="";
    userPassword_="";
    cout<<"�ɹ��ǳ�"<<endl;
}

void AgendaUI::deleteUser(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    cout<<"��DeleteUser��"<<endl;
    std::string userName;
    std::string Password;
    cout<<"Username:";
    while(1){
        getline(cin,userName);

        if(userName.size()==0){
            std::cout<<"It can not be empty!"<<std::endl;
            continue;
        }
        else if(userName!=userName_){
            cout<<"ֻ����ɾ���û�����"<<endl;
            continue;
        }
        break;
    }
    cout<<"Password:";
    while(1){
        getline(cin,Password);
        if(Password.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }
    if(agendaService_.deleteUser(userName,Password)){
        cout<<"�ɹ�ɾ���û�"<<userName<<endl;
        userName_="";
        userPassword_="";
        cout<<"˳��ǳ�"<<endl;
    }
    cout<<"ɾ��ʧ��"<<endl;
}

void AgendaUI::listAllUsers(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    agendaService_.listAllUsers();
}

void AgendaUI::createMeeting(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    cout<<"��CreateMeeting��"<<endl;
    cout<<"UserName:"<<userName_<<endl;
    std::string startdate,enddate,participator,title;

    cout<<"Title:";
    while(1){
        getline(cin,title);
        if(title.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }

    cout<<"Participator:";
    while(1){
        getline(cin,participator);
        if(participator.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }

    cout<<"StartDate:";
    while(1){
        getline(cin,startdate);
        if(startdate.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }

    cout<<"EndDate:";
    while(1){
        getline(cin,enddate);
        if(enddate.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }


    agendaService_.createMeeting(userName_,title,participator,
                                 startdate,enddate);
}

void AgendaUI::listAllMeetings(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    agendaService_.listAllMeetings(userName_);
}

void AgendaUI::listAllSponsorMeetings(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    agendaService_.listAllSponsorMeetings(userName_);
}

void AgendaUI::listAllParticipateMeetings(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    agendaService_.listAllParticipateMeetings(userName_);
}

void AgendaUI::queryMeetingByTitle(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    cout<<"��Query Meeting By Title��"<<endl;
    cout<<"UserName:"<<userName_<<endl;
    std::string title;
    cout<<"Title:";
    while(1){
        getline(cin,title);
        if(title.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }
    agendaService_.meetingQuery(userName_,title);
}

void AgendaUI::queryMeetingByTimeInterval(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    cout<<"��Query Meeting By TimeInterval��"<<endl;
    cout<<"UserName:"<<userName_<<endl;
    std::string startdate,enddate;
    cout<<"StartDate:";
    while(1){
        getline(cin,startdate);
        if(startdate.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }
    cout<<"EndDate:";
    while(1){
        getline(cin,enddate);
        if(enddate.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }
    agendaService_.meetingQuery(userName_,startdate,enddate);
}

void AgendaUI::deleteMeetingByTitle(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    cout<<"��Delete Meeting By Title��"<<endl;
    cout<<"UserName:"<<userName_<<endl;
    std::string title;
    cout<<"Title:";
    while(1){
        getline(cin,title);
        if(title.size()==0){
            cout<<"It can not be empty!"<<endl;
            continue;
        }
        break;
    }
    agendaService_.deleteMeeting(userName_,title);
}

void AgendaUI::deleteAllMeetings(void){
    if(UserStatus()){
        std::cout<<"δ��¼�����¼��ע�ᣩ���ٽ��в�����"<<std::endl;
        return;
    }
    agendaService_.deleteAllMeetings(userName_);
}

#endif
