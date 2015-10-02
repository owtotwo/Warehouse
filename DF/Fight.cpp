#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>


#define npos -1

using namespace std;

enum situation{question=100,choice,title,others};

/*大致想法是，每次取一行到string进行情况分析，实际效果需要：每轮显示一题
  然后获取答案储存起来，清空答案，再提供回答；
  判断string过程采用具体字符对应方式*/

#if 1
int main()
{
    //string分析函数
    situation analysis(const string& pt);
    //问题句处理函数
    string deal(string& pt);
    //提问并判断函数
    bool judge(const string& pt);
    string deal_choice(string& pt);
    string deal_space(string& pt);
    string deal_all_space(string& pt);

    cout<<"**************************************************************"<<endl;
    cout<<"***【Welcome to the sea of Defense_Technology! —— by AT】***"<<endl;
    cout<<"**************************************************************"<<endl<<endl;
    cout<<endl<<"Ps : 1234 could replace ABCD...."<<endl;
    cout<<"     And y is \"yes\", n is \"No\"...."<<endl<<endl;
    //欢迎语
    //打开文件
    ifstream fin("900.txt");
    if(!fin){
        cout<<"fail to open the 900.txt!"<<endl;
        system("pause");
        exit(1);
    }

    //打开成功后先判断跳转位置
    int jump_pos=1;     //题号
    int mark_pos=1;     //记录当前位置
    bool jump_lock=false;//锁定回答暂停阶段

    cout<<"Please enter the number of the question."<<endl
    <<"(Entering “1” means it begins from the first question) "<<endl;
    cout<<"No._\b";

    cin>>jump_pos;
    if(jump_pos<=1){
        jump_pos=1;
    }
    else{
        jump_lock=true;
    }


    //跳转选择
    //声明储存的参数
    string temp,temp1,temp2,answer;



    getline(fin,temp1);              //最起始一句

    //进入循环（到文末结束循环）
    while(!fin.eof()){
        if(mark_pos>=jump_pos){
            jump_lock=false;
        }
        temp=temp1;
        getline(fin,temp1);         //下一句

        if(fin.eof()){
            cout<<"That's All!"<<endl;
            break;
        }


        deal_space(temp);
        deal_choice(temp);
        //system("pause");
        //如果为问题句
        if(question==analysis(temp)){
            //（引用的方式）处理语句中的明文答案并返回答案
            answer=deal(temp);
        }
        //如果为选择句
        else if(choice==analysis(temp)){
            //直接输出（或进行间隔处理，暂时不处理）
            deal_choice(temp);
        }
        else if(title==analysis(temp)){
            //间隔开并直接输出，不进行处理
            if(jump_lock==false)
                cout<<endl;
            continue;
        }
        else if(others==analysis(temp)){
            //cout<<"分析处理出问题了！进了others(应该是空行)"<<endl;
            cout<<temp<<endl;
            continue;
        }
        else{
            //cout<<"分析进了else"<<endl;
            break;
        }




        //上面已经处理完语句的所有情况，下面输出语句
        //if(jump_lock==false)
            cout<<temp<<endl;

        //下面是保证在需要回答问题时暂停并进入回答阶段
        //看来需要一次处理两行，用户结束判断
        //判断标准是下一句为问题，则暂停并提问

        if(choice!=analysis(temp1)){
            //题号位置增加
            mark_pos++;
            //已输出完完整的一题，判断是否在进行跳转，否则进行提问
            if(jump_lock==false){
                //提问
                deal_all_space(answer);
                judge(answer);
                //间隔开一行
                cout<<endl;
            }

        }
        //一个循环结束
    }
    cout<<"That's all! Congratulations!"<<endl;
    return 0;
}
#endif
situation analysis(const string& pt){
    //中心方法是，第一个为数字的则判断为题目(question)；
    //第一个为字母ABCDE的判断为选择(choice)；
    //第一个为书名号的或者为汉数字则判断为标题；
    //否则为其他。

    const char* book_="《";
    const char* three_="三";
    const char* two_="二";
    const char* one_="一";


    string pb=pt;           //用于操作
    if(isdigit(pb[0])){
        //若为数字
        return question;
    }
    else if(pb[0]=='A' || pb[0]=='B' ||
            pb[0]=='C' || pb[0]=='D' || pb[0]=='E'){
        //若为字母ABCDE
        return choice;
    }
    else if(pb[0]==book_[0] || pb[0]==three_[0] ||
            pb[0]==two_[0] || pb[0]==one_[0]){
        //书名号或三或二或一
        return title;
    }
    else{
        return others;
    }
}

string deal(string& pt){
    //大Boss！
    //中心方法是取括号
    //如果括号中间没东西的就去文末的字母
    //如果括号中间有东西就取括号中间的东西并把空格去除
    //有可能是ABCDE或者“对”或“错”或“√”“×”“X”都有！丧病啊简直
    const char* left_kuo="（";
    const char* right_kuo="）";


    int pos=0,mark_pos=0;
    string answer;

    //先判断有无括号


    if(pt.find('(',0)!=npos){
        //找到英文版右括号
        pos=pt.find('(',0);
        for(int i=pos+1;i<pt.size();i++){
            if(pt[i]!=')'){
                answer.push_back(pt[i]);
                pt[i]=' ';
            }
        }
        return answer;
    }
    else{
        pos=pt.find(left_kuo[0],0);
        if(pos==npos){
            //没找到
            //去掉文末字母
            for(string::iterator it=pt.begin();it!=pt.end();it++){
                if(*it=='A' || *it=='B' || *it=='C' || *it=='D' || *it=='E'){
                    answer.push_back((*it));
                    *it=' ';
                }
            }
            return answer;
        }
        else{
            //找到了疑似的，进行判断确认
            while(1){
                if(pt[pos+1]!=left_kuo[1]){
                    //实际上不是，继续找
                    if(pos>=pt.size() || pos==npos){
                        //到末尾了！
                        break;
                    }
                    pos=pt.find(left_kuo[0],pos+1);
                    continue;
                }
                else{
                    //找到了，获取答案直到非英文ABCDE
                    for(int i=pos+2;i<pt.size();i++){
                        if(pt[i]==right_kuo[0] && pt[i+1]==right_kuo[1]){
                            break;
                        }
                        else{
                            answer.push_back(pt[i]);
                            pt[i]=' ';
                        }
                    }
                }

                break;
            }
            if(answer.size()==0){
                //代表括号里没东西
                for(string::iterator it=pt.begin();it!=pt.end();it++){
                    if(*it=='A' || *it=='B' || *it=='C' || *it=='D' || *it=='E'){
                        answer.push_back((*it));
                        *it=' ';
                    }
                }
                //cout<<"到了这"<<endl;
            }
            return answer;
        }
    }
}

#if 0
int main(){
    string answer;
    string sentence="我们国家自古以来就是受到党的领导的！（ABC） ";
    cout<<sentence<<endl;
    answer=deal(sentence);
    cout<<sentence<<endl;
    cout<<"The answer is : "<<answer<<endl;
    return 0;
}
#endif // 0




bool judge(const string& pt){
    //中心方法是，输入的参数是正确答案，需要用户输入答案并匹配
    //输入完后先进行判断正确答案类型
    //再匹配
    string yes="√",collect="对";
    string no="×",wrong="错";
    string answer,answer_temp;

    cout<<"答案是？";
    for(int i=0;i<pt.size();i++){
        cout<<"_\b";
    }
    cin>>answer;

    if(pt==yes || pt==collect){
        if(answer=="y" || answer=="对" || answer=="Y"){
            cout<<"【正确！】"<<endl;
            return true;
        }
        else{
            cout<<"Wrong！答案应该是【 "<<pt<<" 】！"<<endl;
            return false;
        }
    }
    else if(pt==no || pt==wrong || pt=="X"){
        if(answer=="N" || answer=="错" || answer=="n"){
            cout<<"【正确！】"<<endl;
            return true;
        }
        else{
            cout<<"Wrong！答案应该是【 "<<pt<<" 】！"<<endl;
            return false;
        }
    }
    else{
        //应该是正确答案为ABCDE
        //先转换答案后匹配
        for(char x:answer){
            if(x=='1' || tolower(x)=='a')
                answer_temp.push_back('A');
            else if(x=='2' || tolower(x)=='b')
                answer_temp.push_back('B');
            else if(x=='3' || tolower(x)=='c')
                answer_temp.push_back('C');
            else if(x=='4' || tolower(x)=='d')
                answer_temp.push_back('D');
            else if(x=='5' || tolower(x)=='e')
                answer_temp.push_back('E');
            else{
                cout<<"Wrong！答案应该是【 "<<pt<<" 】！"<<endl;
                return false;
            }
        }
        answer=answer_temp;

        if(answer==pt){
            cout<<"【正确！】"<<endl;
            return true;
        }
        else{
            cout<<"Wrong！答案应该是【 "<<pt<<" 】！"<<endl;
            return false;
        }
    }
}
#if 0
int main()
{
    string text="1、我们胜利了》一。A";
    cout<<text<<endl;
    //cout<<"("<<deal(text)<<")"<<endl;

    string temp=deal(text);
    cout<<"("<<temp<<")"<<endl;
    if(temp=="A"){
        cout<<"wtf"<<endl;
    }
    judge("A");
    return 0;
}
#endif

string deal_choice(string& pt){
    string::iterator it=pt.begin();
    for(;it!=pt.end();it++){
        if('?'==(*it)){
            *it=' ';
        }
    }
    return pt;
}

string deal_space(string& pt){
    string answer;
    string::iterator it=pt.begin();
    for(;it!=pt.end();it++){
        if(' '==(*it)){
            *it=' ';
        }
        else{
            break;
        }
    }
    for(;it!=pt.end();it++){
        answer.push_back(*it);
    }
    pt=answer;
    return pt;
}
string deal_all_space(string& pt){
    string x;
    string::iterator it=pt.begin();
    for(;it!=pt.end();it++){
        if(' '!=(*it)){
            x.push_back(*it);
        }
    }
    pt=x;
    return pt;
}
