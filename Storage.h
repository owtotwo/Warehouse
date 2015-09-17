#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include <list>
#include <string>
#include <functional>
#include <istream>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using std::cin;

#include "User.h"
#include "Meeting.h"

class Storage {
  private:
    static Storage *instance_;
    DISALLOW_COPY_AND_ASSIGN(Storage);
    Storage();
    // storage structure with list, or you have better structures
    // e.g. balanced tree
    std::list<User> userList_;
    std::list<Meeting> meetingList_;
    // File IO
    bool readFromFile(const char *fpath);
    bool writeToFile(const char *fpath);
  public:
    // singleton
    static Storage *getInstance(void);
    ~Storage();
    // CRUD for User & Meeting
    // using C++11 Function Template and Lambda Expressions
    void createUser(const User&);
    std::list<User> queryUser(std::function<bool(const User&)> filter);
    // return found users
    int updateUser(std::function<bool(const User&)> filter,
        std::function<void(User&)> switcher);
    // return the number of updated users
    int deleteUser(std::function<bool(const User&)> filter);
    // return the number of deleted users
    void createMeeting(const Meeting&);
    std::list<Meeting> queryMeeting(
                       std::function<bool(const Meeting&)> filter);
    // return found meetings
    int updateMeeting(std::function<bool(const Meeting&)> filter,
        std::function<void(Meeting&)> switcher);
    // return the number of updated meetings
    int deleteMeeting(std::function<bool(const Meeting&)> filter);
    // return the number of deleted meetings
    // File IO
    bool sync(void);
};

Storage* Storage::getInstance(void){
    if(instance_==NULL){
        instance_=new Storage();
    }
    return instance_;
}

Storage::Storage(){
    //导入储存文件
    if(userList_.size()!=0){
        userList_.clear();
    }
    if(meetingList_.size()!=0){
        meetingList_.clear();
    }
}

Storage::~Storage(){
    //这个需要显式调用析构函数吧？
    //写入文件
    writeToFile("AT agenda.txt");
    getchar();
    delete instance_;
    instance_=NULL;
}

void Storage::createUser(const User& pt){
    //将输入参数用户存入UserList即可
    userList_.push_back(pt);
}

std::list<User> Storage::queryUser(
                        std::function<bool(const User&)> filter){
    std::list<User> pt;
    for(std::list<User>::iterator it=userList_.begin();
                                        it!=userList_.end();it++){
        if(filter((*it))==true){
            pt.push_back((*it));
        }
    }
    return pt;
}
//lambda函数为判断list中的内容是否符合
// return found users

int Storage::updateUser(std::function<bool(const User&)> filter,
        std::function<void(User&)> switcher){
    //这个其实是增加用户或替换用户吧
    //filter();
    //switcher();
    return userList_.size();
}
// return the number of updated users

int Storage::deleteUser(std::function<bool(const User&)> filter){
    //filter();
    return userList_.size();
}
// return the number of deleted users

void Storage::createMeeting(const Meeting& pt){
    meetingList_.push_back(pt);
}

std::list<Meeting> Storage::queryMeeting(
                    std::function<bool(const Meeting&)> filter){
    std::list<Meeting> meeting;
    std::list<Meeting>::iterator it=meetingList_.begin();
    for(;it!=meetingList_.end();it++){
        if(filter((*it))){
            meeting.push_back((*it));
        }
    }
    return meeting;
}
// return found meetings
#if 1
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
        std::function<void(Meeting&)> switcher){
    return meetingList_.size();
}
// return the number of updated meetings
int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter){
    std::list<Meeting>::iterator it=meetingList_.begin();
    int first_size=meetingList_.size();
    for(;it!=meetingList_.end();it++){
        if(filter((*it))){
            meetingList_.erase(it);
        }
    }
    int last_size=meetingList_.size();
    return first_size-last_size;
}
// return the number of deleted meetings
// File IO
std::string followme(ifstream& pt){
    //从传入指针位置到下一个 " 符号停止，返回string
    char ch=0;
    std::string mark;
    bool tag=false;
    while(1){               //范例："conclusion","facebook"\n
        pt.get(ch);
        if(ch!='\"' && ch!=',' && ch!='\n'){
            mark+=ch;
            if(tag==false){
                tag=true;
            }
        }
        if(tag==true)
            break;
    }
    if(mark.size()!=0)
            return mark;
    return "FollowmeWrong";
}

bool Storage::readFromFile(const char *fpath){
    std::ifstream pfile;
    pfile.open(fpath);
    if(!pfile){
        cout<<"打开文件失败"<<endl;
        return false;
    }
    //pfile.seekg(0,ios::beg);            //保证在起点位置
    std::string temp;
    User anyone;
    Meeting everyone;
    //std::list<User> userTemp;
    //std::list<Meeting> meetingTemp;
    int step=0;
    while(!pfile.eof()){                //没到末尾则继续提取关键字
        temp=followme(pfile);
        if(temp=="UserCollections:"){
            step=1;
        }
        if(temp=="MeetingCollections:"){
            step=5;
        }
        if(temp.size()!=0){
            if(step==1){
                anyone.setName(temp);
                step=2;
            }
            else if(step==2){
                anyone.setPassword(temp);
                step=3;
            }
            else if(step==3){
                anyone.setEmail(temp);
                step=4;
            }
            else if(step==4){
                anyone.setPhone(temp);
                step=1;
            }
            else if(step==5){
                everyone.setSponsor(temp);
                step=6;
            }
            else if(step==6){
                everyone.setTitle(temp);
                step=7;
            }
            else if(step==7){
                everyone.setParticipator(temp);
                step=8;
            }
            else if(step==8){
                everyone.setStartDate(Date::stringToDate(temp));
                step=9;
            }
            else if(step==9){
                everyone.setEndDate(Date::stringToDate(temp));
                step=5;
            }
            else{
                pfile.close();
                return false;
            }
        }
        if(step==1){
            userList_.push_back(anyone);
        }
        if(step==5){
            meetingList_.push_back(everyone);
        }
    }
    return true;
}

bool Storage::writeToFile(const char *fpath){
    std::ofstream fout;
    fout.open(fpath);
    if(!fout.is_open()){
        return false;
    }

    fout<<"\"UserCollections:\""<<endl;
    for(User x : userList_){
        fout<<'\"'<<x.getName()<<"\",\""<<x.getPassword()<<"\",\""
        <<x.getEmail()<<"\",\""<<x.getPhone()<<'\"'<<endl;
    }
    fout<<"\"MeetingCollections:\""<<endl;
    for(Meeting y : meetingList_){
        fout<<'\"'<<y.getSponsor()<<"\",\""<<y.getTitle()<<"\",\""
        <<y.getParticipator()<<"\",\""
        <<Date::dateToString(y.getStartDate())<<"\",\""
        <<Date::dateToString(y.getEndDate())<<'\"'<<endl;
    }
    fout.close();
    return true;
}

bool Storage::sync(void){
    //大Boss:同步
    //if(writeToFile("AT agenda.txt")){
    //    return true;
    //}

    //难道同步是读取出来的意思？
    if(readFromFile("AT agenda.txt")){
        return true;
    }
    return false;
}
#endif // 0
#endif
