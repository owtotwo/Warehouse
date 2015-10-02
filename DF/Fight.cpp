#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>


#define npos -1

using namespace std;

enum situation{question=100,choice,title,others};

/*�����뷨�ǣ�ÿ��ȡһ�е�string�������������ʵ��Ч����Ҫ��ÿ����ʾһ��
  Ȼ���ȡ�𰸴�����������մ𰸣����ṩ�ش�
  �ж�string���̲��þ����ַ���Ӧ��ʽ*/

#if 1
int main()
{
    //string��������
    situation analysis(const string& pt);
    //����䴦����
    string deal(string& pt);
    //���ʲ��жϺ���
    bool judge(const string& pt);
    string deal_choice(string& pt);
    string deal_space(string& pt);
    string deal_all_space(string& pt);

    cout<<"**************************************************************"<<endl;
    cout<<"***��Welcome to the sea of Defense_Technology! ���� by AT��***"<<endl;
    cout<<"**************************************************************"<<endl<<endl;
    cout<<endl<<"Ps : 1234 could replace ABCD...."<<endl;
    cout<<"     And y is \"yes\", n is \"No\"...."<<endl<<endl;
    //��ӭ��
    //���ļ�
    ifstream fin("900.txt");
    if(!fin){
        cout<<"fail to open the 900.txt!"<<endl;
        system("pause");
        exit(1);
    }

    //�򿪳ɹ������ж���תλ��
    int jump_pos=1;     //���
    int mark_pos=1;     //��¼��ǰλ��
    bool jump_lock=false;//�����ش���ͣ�׶�

    cout<<"Please enter the number of the question."<<endl
    <<"(Entering ��1�� means it begins from the first question) "<<endl;
    cout<<"No._\b";

    cin>>jump_pos;
    if(jump_pos<=1){
        jump_pos=1;
    }
    else{
        jump_lock=true;
    }


    //��תѡ��
    //��������Ĳ���
    string temp,temp1,temp2,answer;



    getline(fin,temp1);              //����ʼһ��

    //����ѭ��������ĩ����ѭ����
    while(!fin.eof()){
        if(mark_pos>=jump_pos){
            jump_lock=false;
        }
        temp=temp1;
        getline(fin,temp1);         //��һ��

        if(fin.eof()){
            cout<<"That's All!"<<endl;
            break;
        }


        deal_space(temp);
        deal_choice(temp);
        //system("pause");
        //���Ϊ�����
        if(question==analysis(temp)){
            //�����õķ�ʽ����������е����Ĵ𰸲����ش�
            answer=deal(temp);
        }
        //���Ϊѡ���
        else if(choice==analysis(temp)){
            //ֱ�����������м��������ʱ������
            deal_choice(temp);
        }
        else if(title==analysis(temp)){
            //�������ֱ������������д���
            if(jump_lock==false)
                cout<<endl;
            continue;
        }
        else if(others==analysis(temp)){
            //cout<<"��������������ˣ�����others(Ӧ���ǿ���)"<<endl;
            cout<<temp<<endl;
            continue;
        }
        else{
            //cout<<"��������else"<<endl;
            break;
        }




        //�����Ѿ������������������������������
        //if(jump_lock==false)
            cout<<temp<<endl;

        //�����Ǳ�֤����Ҫ�ش�����ʱ��ͣ������ش�׶�
        //������Ҫһ�δ������У��û������ж�
        //�жϱ�׼����һ��Ϊ���⣬����ͣ������

        if(choice!=analysis(temp1)){
            //���λ������
            mark_pos++;
            //�������������һ�⣬�ж��Ƿ��ڽ�����ת�������������
            if(jump_lock==false){
                //����
                deal_all_space(answer);
                judge(answer);
                //�����һ��
                cout<<endl;
            }

        }
        //һ��ѭ������
    }
    cout<<"That's all! Congratulations!"<<endl;
    return 0;
}
#endif
situation analysis(const string& pt){
    //���ķ����ǣ���һ��Ϊ���ֵ����ж�Ϊ��Ŀ(question)��
    //��һ��Ϊ��ĸABCDE���ж�Ϊѡ��(choice)��
    //��һ��Ϊ�����ŵĻ���Ϊ���������ж�Ϊ���⣻
    //����Ϊ������

    const char* book_="��";
    const char* three_="��";
    const char* two_="��";
    const char* one_="һ";


    string pb=pt;           //���ڲ���
    if(isdigit(pb[0])){
        //��Ϊ����
        return question;
    }
    else if(pb[0]=='A' || pb[0]=='B' ||
            pb[0]=='C' || pb[0]=='D' || pb[0]=='E'){
        //��Ϊ��ĸABCDE
        return choice;
    }
    else if(pb[0]==book_[0] || pb[0]==three_[0] ||
            pb[0]==two_[0] || pb[0]==one_[0]){
        //�����Ż��������һ
        return title;
    }
    else{
        return others;
    }
}

string deal(string& pt){
    //��Boss��
    //���ķ�����ȡ����
    //��������м�û�����ľ�ȥ��ĩ����ĸ
    //��������м��ж�����ȡ�����м�Ķ������ѿո�ȥ��
    //�п�����ABCDE���ߡ��ԡ��򡰴��򡰡̡���������X�����У�ɥ������ֱ
    const char* left_kuo="��";
    const char* right_kuo="��";


    int pos=0,mark_pos=0;
    string answer;

    //���ж���������


    if(pt.find('(',0)!=npos){
        //�ҵ�Ӣ�İ�������
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
            //û�ҵ�
            //ȥ����ĩ��ĸ
            for(string::iterator it=pt.begin();it!=pt.end();it++){
                if(*it=='A' || *it=='B' || *it=='C' || *it=='D' || *it=='E'){
                    answer.push_back((*it));
                    *it=' ';
                }
            }
            return answer;
        }
        else{
            //�ҵ������Ƶģ������ж�ȷ��
            while(1){
                if(pt[pos+1]!=left_kuo[1]){
                    //ʵ���ϲ��ǣ�������
                    if(pos>=pt.size() || pos==npos){
                        //��ĩβ�ˣ�
                        break;
                    }
                    pos=pt.find(left_kuo[0],pos+1);
                    continue;
                }
                else{
                    //�ҵ��ˣ���ȡ��ֱ����Ӣ��ABCDE
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
                //����������û����
                for(string::iterator it=pt.begin();it!=pt.end();it++){
                    if(*it=='A' || *it=='B' || *it=='C' || *it=='D' || *it=='E'){
                        answer.push_back((*it));
                        *it=' ';
                    }
                }
                //cout<<"������"<<endl;
            }
            return answer;
        }
    }
}

#if 0
int main(){
    string answer;
    string sentence="���ǹ����Թ����������ܵ������쵼�ģ���ABC�� ";
    cout<<sentence<<endl;
    answer=deal(sentence);
    cout<<sentence<<endl;
    cout<<"The answer is : "<<answer<<endl;
    return 0;
}
#endif // 0




bool judge(const string& pt){
    //���ķ����ǣ�����Ĳ�������ȷ�𰸣���Ҫ�û�����𰸲�ƥ��
    //��������Ƚ����ж���ȷ������
    //��ƥ��
    string yes="��",collect="��";
    string no="��",wrong="��";
    string answer,answer_temp;

    cout<<"���ǣ�";
    for(int i=0;i<pt.size();i++){
        cout<<"_\b";
    }
    cin>>answer;

    if(pt==yes || pt==collect){
        if(answer=="y" || answer=="��" || answer=="Y"){
            cout<<"����ȷ����"<<endl;
            return true;
        }
        else{
            cout<<"Wrong����Ӧ���ǡ� "<<pt<<" ����"<<endl;
            return false;
        }
    }
    else if(pt==no || pt==wrong || pt=="X"){
        if(answer=="N" || answer=="��" || answer=="n"){
            cout<<"����ȷ����"<<endl;
            return true;
        }
        else{
            cout<<"Wrong����Ӧ���ǡ� "<<pt<<" ����"<<endl;
            return false;
        }
    }
    else{
        //Ӧ������ȷ��ΪABCDE
        //��ת���𰸺�ƥ��
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
                cout<<"Wrong����Ӧ���ǡ� "<<pt<<" ����"<<endl;
                return false;
            }
        }
        answer=answer_temp;

        if(answer==pt){
            cout<<"����ȷ����"<<endl;
            return true;
        }
        else{
            cout<<"Wrong����Ӧ���ǡ� "<<pt<<" ����"<<endl;
            return false;
        }
    }
}
#if 0
int main()
{
    string text="1������ʤ���ˡ�һ��A";
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
