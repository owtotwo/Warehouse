#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>

#include <cstdio>

using namespace std;

// LR(0)ʵ�ֳ���
// ���ݽṹ �����㷨
// ע��I/O


//��������Value�����ݽṹ��δ������ַ���string

// Ŀ��������ͼ�����ɱ�
// ��ͼ��
//      ���ݽṹ����� �� ��Ŀ�� ������Ŀ ��Ŀ��
//      �������հ����� First������ goto closure

class Value {
public:

    // ***********************
    bool isTerminal;    //��ʱû��ò��
    bool isChar;
    string s;
    // ***********************
    Value(char c, bool ischar = false, bool isterminal = false) {
        s += c;
        isChar = ischar;
        isTerminal = isterminal;
    }
    Value(string stemp = "", bool ischar = false, bool isterminal = false)
                    : s(stemp), isChar(ischar), isTerminal(isterminal) {}
    Value(const Value& pt) {
        isChar = pt.isChar;
        s = pt.s;
        isTerminal = pt.isTerminal;
    }
    friend ostream& operator<<(ostream &os, const Value& pt);
    bool operator<(const Value& pt) {
        return s < pt.s;
    }
    friend bool operator==(const Value& a, const Value& b) {
        return (a.s == b.s && a.isChar == b.isChar);
    }
    friend bool operator<(const Value& a, const Value& b) {
        return a.s < b.s;
    }
};

class task {
public:
    // ***********************
    Value leftChar;
    std::vector<Value> rchar;
    // ***********************

    task() {}
    task(Value& lchar) : leftChar(lchar) {}
    task(const task& pt) {
        leftChar = pt.leftChar;
        rchar = pt.rchar;
    }
    friend ostream& operator<<(ostream &, task&);
};

ostream& operator<<(ostream &os, const Value& pt) {
    if (pt.isChar) cout << '\'' << pt.s << '\'';
    else cout << pt.s;
    return os;
}

ostream& operator<<(ostream &os, task& pt) {
    cout << pt.leftChar << " -> ";
    for (Value& x : pt.rchar) {
        cout << x << ' ';
    }
    cout << ';';
    return os;
}

class taskList {
public:
    // ***********************
    std::vector<task> tasklist;
    // ***********************

    taskList() {}
    taskList(const taskList& pt) {
        tasklist = pt.tasklist;
    }
    friend ostream& operator<<(ostream &os, taskList& pt);
};

ostream& operator<<(ostream &os, taskList& pt) {
    for (task& x : pt.tasklist)
        cout << x << endl;
    return os;
}

#if 0
class Edge {
public:
    // ***********************
    char c;
    Node* nextNode;
    // ***********************

    Edge(char ch, Node *nextp = NULL) : c(ch), nextNode(nextp) {}
};
#endif

class taskMark {
public:
    // ***********************
    int taskNum, index;
    bool isEnd;
    // ***********************

    taskMark(int task_num, int Index) : taskNum(task_num), index(Index), isEnd(false) {}
    friend bool operator<(const taskMark& a ,const taskMark& b) {
        if (a.taskNum < b.taskNum) return true;
        else if (a.taskNum == b.taskNum) return a.index < b.index;
        else return false;
    }
    friend bool operator==(const taskMark& a ,const taskMark& b) {
        return (a.taskNum == b.taskNum && a.index == b.index);
    }
    friend bool operator!=(const taskMark& a ,const taskMark& b) {
        return !(a == b);
    }
    friend ostream& operator<<(ostream& os, const taskMark& pt) {
        cout << "taskNum = " << pt.taskNum << " index = " << pt.index ;
        return os;
    }
    void disp(const taskList& pt) const {
        task temp = pt.tasklist[taskNum];
        cout << temp.leftChar << " -> ";
        for (int i = 0; i < temp.rchar.size(); i++) {
            if (i == index) cout << "��" ;
            cout << temp.rchar[i] << " ";
        }
        if (index == temp.rchar.size()) cout << "��";
        cout << endl;
    }
};

class Node {
public:
    static int id;
    static void addID() {
        id++;
    }

    // ***********************
    int ID;
    bool isReduced;
    std::set<taskMark> taskSet;
    std::map<Value, Node*> edges;
    // ***********************

    Node() {
        ID = id;
        addID();
        isReduced = false;
    }
    bool operator<(const Node& pt) {
        return ID < pt.ID;
    }
    //friend ostream& operator<<(ostream &os, const Node& pt) {
    void disp(const taskList& pt) {
        cout << "ID: " << ID << endl;
        for (const taskMark &x : taskSet) {
            x.disp(pt);
        }
        cout << endl;
    }
};

class LRgraph {
public:
    // ***********************
    Node* start;
    std::set<Node*> nodeSet;
    taskList taskTable;
    // ***********************
};


// ��ȡ��ĿTask�е�FirstԪ��Value
Value getFirstValueFromTaskMark(const taskMark& tempTask, const taskList& tempTaskList) {

    task tempTaskMark = tempTaskList.tasklist[tempTask.taskNum];    // ĳ����Ŀ
    Value ret = tempTaskMark.rchar[tempTask.index];
    return ret;
}

// �ж�Task�Ƿ��Լ״̬(����ǵ�index�Ƿ�Ϊĩ)
bool isReduced(const taskMark &tempTask, const taskList& tempTaskList) {

    task tempTaskMark = tempTaskList.tasklist[tempTask.taskNum];    // ĳ����Ŀ
    if (tempTask.index == tempTaskMark.rchar.size()) return true;
    else return false;
}

std::set<taskMark> closure(const taskMark& pt, const taskList& tl) {
    // Input : (1, 0)
    // Output : a set of taskMark

    // S -> E $;
    // E -> T + E
    //    | T;
    // T -> n;
    // n -> '0' | '1';

    // �ж��Ƿ�Ϊĩβ ���򷵻ؿռ�
    // ����ִ�����²���
    // ȡ (index + 1) ����Value
    // ������ս�� �򷵻ؿռ�
    // ������ս�� ��
    // ��taskList�е�leftChar����
    // ���� �����set�� �ʹ�����Ĺ�������qu��

    std::set<taskMark> ret;
    // ����Ҳ��հ�һ����
    ret.insert(pt);

    if (pt.isEnd) return ret;

    // �����ж����ܳ����ѽ�����taskMark
    std::queue<taskMark> qu;
    qu.push(pt);


    while (!qu.empty()) {
        taskMark temp = qu.front();
        qu.pop();

        // ȡ��First��Value
        Value tempValue = getFirstValueFromTaskMark(temp, tl);

        for (int i = 0; i < tl.tasklist.size(); i++) {
            if (tempValue == tl.tasklist[i].leftChar) {
                taskMark newTaskMark(i, 0);
                // ���Ѵ��ڴ�taskMark �򲻴��� ����
                if (ret.find(newTaskMark) == ret.end()) {
                    // û�ҵ� �½�һ��
                    if (isReduced(newTaskMark, tl)) newTaskMark.isEnd = true;
                    ret.insert(newTaskMark);
                    qu.push(newTaskMark);
                }
            }
        }

    }

    return ret;
}

void closure_deal(std::set<taskMark>& pt, const taskList& tl) {
    std::set<taskMark> tempClosureSet;
    for (const taskMark &x : pt)
        for (const taskMark &y : closure(x, tl))
            tempClosureSet.insert(y);
    pt = tempClosureSet;
}

LRgraph creatLRgraph(const taskList& pt) {

    LRgraph graph;
    graph.taskTable = pt;

    Node *startNode = new Node;                 // �������
    taskMark tempTaskMark(0, 0);                // ��������һ��task
    if (isReduced(tempTaskMark, pt)) tempTaskMark.isEnd = true;
    startNode->taskSet.insert(tempTaskMark);    // ���뵽tasklist
    closure_deal(startNode->taskSet, pt);       // �հ���չ

    graph.nodeSet.insert(startNode);            // ÿ�½�һ��node������nodeSet
    graph.start = startNode;

    // ���Ƚ����г�ʼ����S' -> S $
    // Ȼ������task��First�ıհ�
    // ����������taskList
    // Ȼ����taskList��First���ռ� ���ڲ�����һ�����
    // �����task����һ��tempNode ������set���ѯ�Ƿ��Ѵ���
    // �������� �������ָ����
    // �������� ��������һ����� ��ָ����
    // ���������������Ķ���Qu��
    // ��������Ŀ������� ���һ��ѭ��
    // ÿ��ѭ����ȡ��������ǰԪ�� ��������
    // ���Ǳհ����� Ȼ�����task����
    //
    // ���ǵô���graph��start

    std::queue<Node*> qu;
    qu.push(startNode);     // ���빤������

    while (!qu.empty()) {   //����ÿ�������н�� ���������

        // ������ȡ���
        Node* tempNode = qu.front();
        qu.pop();

        cout << "ȡ���Ľ����" << endl;
        tempNode->disp(pt);

        /**********************************************
        // �Խ�����Ѵ��ڵ�tasks �ñհ�������ʣ��task
        std::set<taskMark> tempClosureSet;
        for (const taskMark &x : tempNode->taskSet)
            for (const taskMark &y : closure(x, pt))
                tempClosureSet.insert(y);
        tempNode->taskSet = tempClosureSet;
        ***********************************************/

        // *************** ������ ******************
        std::map<Value, std::set<taskMark>> virtualMap;

        // ����ÿһ��task
        for (const taskMark &x : tempNode->taskSet) {

            if (x.isEnd) {
                tempNode->isReduced = true;
                cout << "�ѵ�ĩβ" << endl;
                continue;
            }

            Value tempValue = getFirstValueFromTaskMark(x, pt);     // ȡ����һ��ֵ
            taskMark tempTMark(x.taskNum, x.index + 1);             // �����µ�taskMark
            if (isReduced(tempTMark, pt)) tempTMark.isEnd = true;   // ȷ������
            virtualMap[tempValue].insert(tempTMark);                // ���뵽αӳ����
        }


        for (std::pair<const Value, std::set<taskMark>> &x : virtualMap) {

            closure_deal(x.second, pt);

            bool ok = false;
            for (Node* y : graph.nodeSet) {
                if (y->taskSet == x.second) {
                    cout << "�Ѵ��ڴ˽��ID = " << y->ID << " ������" << endl;
                    ok = true;
                    tempNode->edges[x.first] = y;
                }
            }

            if (!ok) {
                Node *tNode = new Node;
                tNode->taskSet = x.second;
                tempNode->edges[x.first] = tNode;
                cout << "�½����ID = " << tNode->ID << endl;
                graph.nodeSet.insert(tNode);
                qu.push(tNode);
            }
        }







        // *************** ������ ******************

        /* *************** ��ʱ���� ****************
        // �������task
        for (const taskMark &x : tempNode->taskSet) {

            cout << "���ڴ���taskMark " ;
            x.disp(pt);

            // �ȿ��Ƿ�ΪReduced �������������һ��task
            if (x.isEnd) {
                tempNode->isReduced = true;
                cout << "�ѵ�ĩβ" << endl;
                continue;
            }

            // �Խ����ÿ��task Ӧ�Ȳ�����Ӧ�ıߺͶ�Ӧ��α���
            // ��������ٶ�ÿ���ߺ�α��㶼���б���
            // ���н���Ѵ��� ��ָ���Ѵ����Ǹ�
            // ������ ��newһ�����

            std::map<Value, std::set<taskMark>> virtualMap;

            // Ѱ���Ƿ��Ѵ��ڱ�
            Value tempValue = getFirstValueFromTaskMark(x, pt);
            if (virtualMap.find(tempValue) != virtualMap.end())
                cout << "�Ѵ��ڴ˱�" << endl;
            taskMark tempTMark(x.taskNum, x.index + 1);
            if (isReduced(tempTMark, pt)) tempTMark.isEnd = true;
            virtualMap[tempValue].insert(tempTMark);

            // ����virtualMap ������
            for (std::pair<const Value, std::set<taskMark>> &y : virtualMap) {
                bool ok = false;
                for (Node* z : graph.nodeSet) {
                    if (z->taskSet == y.second) {
                        cout << "�Ѵ��ڴ˽�� ������" << endl;
                        ok = true;
                        tempNode->edges[y.first] = z;
                    }
                }
                if (!ok) {
                    Node *tNode = new Node;
                    tNode->taskSet = y.second;
                    tempNode->edges[y.first] = tNode;
                    cout << "�½����ID = " << tNode->ID << endl;
                    graph.nodeSet.insert(tNode);
                    qu.push(tNode);
                }
            }
        }
        *************** ��ʱ���� *****************/
    }
    return graph;
}
/* ******************* �����ʱû�ɹ� ���� *****************************

            // Ѱ���Ƿ��Ѵ��ڱ�
            Value tempValue = getFirstValueFromTaskMark(x, pt);
            Node *tNode = NULL;
            if (tempNode->edges.find(tempValue) == tempNode->edges.end()) {
                // û�ҵ� �������Ƿ��Ѿ����������

                tempNode->edges[tempValue] = tNode;
                tNode = new Node;
            } else {
                // �Ѵ��� ȡ�����
                tNode = tempNode->edges[tempValue];
            }
            // ����������Ķ�Ӧ��task
            taskMark temptaskmark(x.taskNum, x.index + 1);
            tNode.taskSet.insert(temptaskmark);
********************************************************************** */








// ******************** //
// *****������Ŀ��***** //
// ******************** //
taskList creatTaskTable(const char* address) {
    /*
    FILE* fp = fopen(address, "rt");
    if (!fp) {
        printf("Wrong!");
        return taskList;
    }
    */
    bool isValidTask(const task &pt);

    freopen(address, "rt", stdin);
    if (stdin == NULL) {
        cout << "����" << endl;
        exit(1);
    }
    cout << "*******************************" << endl;

    // Form :
    //
    // S : E $;
    // E : T '+' E
    //   | T;
    // T : n;
    // n : '0' | '1' | ... | '9';
    // ;

    // ������
    // ÿ����俪ͷ����NonTerminal Char
    // Ȼ����ð��':'
    // Ȼ������ĸ���õ�����������ַ�
    // Сд��ĸ���ַ������ս�Terminal
    // ��'|'�����
    // �ֺŽ���
    // �ֺſ�ͷ���ʾȫ�Ľ���

    taskList retList;

    // ����ÿһ��

    while (true) {
        char c = 0;
        task retTask;

        // �ų��ո�
        while (isspace(c = getchar()));
        cout << "��һ���ַ�Ϊ" << c << endl;
        if (!isalpha(c)) break; // �������е�һ���ǿո��ַ�������ĸ �����ѭ�� ��';'

        // ��ȷ�ϵ�һ��Ϊ��ĸ ���յ�һ��NonTerminal Token
        Value tempValue(c, false);
        while (isalpha(c = getchar()))
            tempValue.s += c;
        retTask.leftChar = tempValue;   // �������ֵ S -> ...

        // ����ð��
        while (isspace(c)) c = getchar();
        if (c != ':') {
            string temps = "expected \':\' but \' ";
            temps += c;
            temps += "\' ";
            throw temps;
        }

        // ��ȷ��Ϊð��
        c = getchar();
        while (true) {          // ����ÿ����ֵ
            while (isspace(c)) c = getchar();

            if (c == '\'') {            // �����ַ�'c'
                c = getchar();

                if (c == '\\') {
                    c = getchar();
                    switch(c) {
                        case 'n' : c = '\n'; break;
                        case 'b' : c = '\b'; break;
                        case 't' : c = '\t'; break;
                        case 'r' : c = '\r'; break;
                        case 'v' : c = '\v'; break;
                        default : break;
                    }
                }
                Value tempV(c, true);

                if ((c = getchar()) != '\'') {
                    throw "expected \'\\\'\' ";
                } else {
                    retTask.rchar.push_back(tempV);
                }
            } else if (isalpha(c)) {      // �ַ���
                Value tempV(c, false);
                while (isalpha(c = getchar()))
                    tempV.s += c;
                retTask.rchar.push_back(tempV);
                continue;
            } else if (c == '|') {
                // �Ȱ��������̽���
                retList.tasklist.push_back(retTask);
                // �����ֵ ������ֵ
                retTask.rchar.clear();
                // ����
            } else if (c == ';'){
                cout << "���һ���������" << endl;
                // �ж�����Ƿ�Ϸ�
                if (!isValidTask(retTask)) {
                    cout << "��䲻�Ϸ�" << endl;
                    throw "Invalid Syntax";
                }
                break;
            } else {
                cout << "���ݲ����� Ϊ�ַ�" << c << " ����ִ����һ���������" << endl;
                break;
            }
            c = getchar();
        }
        cout << "�����taskΪ" << retTask << endl;
        retList.tasklist.push_back(retTask);    // ���봦�����һ��task
    }
    return retList;
}

bool isValidTask(const task &pt) {
    // �ж����� S : T '+' B ; ����Ƿ�Ϸ�
    return pt.rchar.size() != 0 && pt.leftChar.s.length() > 0;
}




// ******************** //
// *****������ת��***** //
// ******************** //

/*********** �����ʽ ************
    From :
    ---------------------
        ACTION  |  GOTO
        n  $  + |  S  T
    0   s1      |  3  2
    1   r3 r3 r3|
    2         s4|
    3      ac   |
    4   s1      |  5  2
    5   r1 r1 r1|
    ---------------------
**********************************/

class JumpTable {
public:
    // ***************************************** //
    int stateNum;
    std::map<Value, std::vector<pair<char, int>>> Action;
    std::map<Value, std::vector<int>> Goto;
    // ***************************************** //

    JumpTable(int statenum) : stateNum(statenum){}
    friend ostream& operator<<(ostream& os, const JumpTable& pt) {
        cout << "[ACTION]" << endl;
        for (const pair<Value, std::vector<pair<char, int>>> &x : pt.Action) {
            cout << "Value : " << x.first << endl;
            for (const pair<char, int> &y : x.second) {
                cout << y.first << y.second << " ";
            }
            cout << endl;
        }
        cout << "[GOTO]" << endl;
        for (const pair<Value, std::vector<int>> &x : pt.Goto) {
            cout << "Value : " << x.first << endl;
            for (const int &y : x.second)
                cout << " " << y << " ";
            cout << endl;
        }
        return os;
    }
};

std::set<Value> FollowSet(const Value& value, const taskList& tl) {
    std::set<Value> ret;
    for (const task &x : tl.tasklist) {
        // i.e. S -> E + F $;
        for (int i = 0; i < x.rchar.size(); i++) {
            if (x.rchar[i] == value) {
                if (i + 1 < x.rchar.size()) {
                    ret.insert(x.rchar[i + 1]);
                }
            }
        }
    }
    for (const Value &x : ret) cout << x << " ";
    cout << endl;
    return ret;
}

JumpTable creatJumpTable(const LRgraph &graph) {

    int stateNum = graph.nodeSet.size();
    JumpTable retJumpTable(stateNum);

    taskList tl = graph.taskTable;
    retJumpTable.stateNum = stateNum;

    std::vector<Node*> nodes(stateNum);
    for (Node* x : graph.nodeSet) nodes[x->ID] = x;

    for (int i = 0; i < stateNum; i++) {
        // ���������
        Node* tempNode = nodes[i];
        int state = tempNode->ID;
        cout << "�ִ���ID = " << state << endl;

        // �Ա߲���
        bool hasEdge = false;
        for (pair<const Value, Node*> &x : tempNode->edges) {
            Value tempValue = x.first;
            pair<char, int> tempPair('s', x.second->ID);
            if (!hasEdge) hasEdge = true;
            if (tempValue.isChar) {

                if (retJumpTable.Action[tempValue].size() == 0)
                    retJumpTable.Action[tempValue].assign(stateNum, pair<char, int>('e', -1));

                retJumpTable.Action[tempValue][state] = tempPair;
            } else {
                if (retJumpTable.Goto[tempValue].size() == 0)
                    retJumpTable.Goto[tempValue].assign(stateNum, -1);
                retJumpTable.Goto[tempValue][state] = x.second->ID;
            }
        }
        if (hasEdge && tempNode->isReduced) {
            // �ƽ�-��Լ ��ͻ
            cout << "!!!!!!!!!!!!!!!!�ƽ�-��Լ ��ͻ!!!!!!!!!!!!!!!!!!" << endl;
            std::set<Value> followS;
            std::vector<std::set<Value>> followRvector, tempFollowSet;
            // ��task����
            for (const taskMark &x : tempNode->taskSet) {
                if (x.isEnd) {
                    followRvector.push_back(FollowSet(tl.tasklist[x.taskNum].leftChar, tl));
                } else {
                    followS.insert(getFirstValueFromTaskMark(x, tl));
                }
            }

            tempFollowSet = followRvector;
            followRvector.push_back(followS);
            sort(followRvector.begin(), followRvector.end());
            auto pos = unique(followRvector.begin(), followRvector.end());
            if (pos != followRvector.end()) {
                cout << "����conflict��" << endl;
                exit(1);
            } else {
                int i = 0;
                for (const taskMark &x : tempNode->taskSet) {
                    if (x.isEnd) {
                        pair<char, int> tempPair('r', x.taskNum);

                        for (const Value &y : tempFollowSet[i]) {

                            if (retJumpTable.Action[y].size() == 0)
                                retJumpTable.Action[y].assign(stateNum, pair<char, int>('e', 0));
                            retJumpTable.Action[y][state] = tempPair;
                        }
                        i++;
                    }
                }
            }
        } else if (tempNode->isReduced){
            // ��Լ
            for (const taskMark &x : tempNode->taskSet) {
                pair<char, int> tempPair('r', x.taskNum);
                if (x.isEnd) {
                    for (const Value &y : FollowSet(tl.tasklist[x.taskNum].leftChar, tl)) {
                        if (retJumpTable.Action[y].size() == 0)
                            retJumpTable.Action[y].assign(stateNum, pair<char, int>('e', 0));
                        retJumpTable.Action[y][state] = tempPair;
                    }
                }
            }
        }
    }

    return retJumpTable;
}

int Node::id = 0;

int main()
{
    cout << "LR(0)!" << endl;
    try {
        taskList templist = creatTaskTable("C://Users/wh/Desktop/ali.txt");
        cout << templist << endl;
        LRgraph tempGraph = creatLRgraph(templist);
        JumpTable tempJumpTable = creatJumpTable(tempGraph);
        cout << tempJumpTable << endl;
        streambuf* coutBuf = cout.rdbuf();
        ofstream fout("C://Users/wh/Desktop/aliba.txt");
        streambuf* foutBuf = fout.rdbuf();
        cout.rdbuf(foutBuf);
        cout << tempJumpTable << endl;
        cout.rdbuf(coutBuf);
    } catch (const char* errStr){
        fprintf(stderr, "%s\n", errStr);
        exit(1);
    }
    return 0;
}
