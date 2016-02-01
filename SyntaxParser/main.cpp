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

// LR(0)实现尝试
// 数据结构 分析算法
// 注意I/O


//遇到的问Value的数据结构如何处理单独字符和string

// 目标是生成图再生成表
// 构图：
//      数据结构：结点 边 项目集 单个项目 项目表
//      方法：闭包计算 First集计算 goto closure

class Value {
public:

    // ***********************
    bool isTerminal;    //暂时没用貌似
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
            if (i == index) cout << "·" ;
            cout << temp.rchar[i] << " ";
        }
        if (index == temp.rchar.size()) cout << "·";
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


// 获取项目Task中的First元素Value
Value getFirstValueFromTaskMark(const taskMark& tempTask, const taskList& tempTaskList) {

    task tempTaskMark = tempTaskList.tasklist[tempTask.taskNum];    // 某条项目
    Value ret = tempTaskMark.rchar[tempTask.index];
    return ret;
}

// 判断Task是否归约状态(即标记点index是否为末)
bool isReduced(const taskMark &tempTask, const taskList& tempTaskList) {

    task tempTaskMark = tempTaskList.tasklist[tempTask.taskNum];    // 某条项目
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

    // 判断是否为末尾 是则返回空集
    // 否则执行以下操作
    // 取 (index + 1) 处的Value
    // 如果是终结符 则返回空集
    // 如果非终结符 则
    // 在taskList中的leftChar中找
    // 若有 则放在set中 和待处理的工作队列qu中

    std::set<taskMark> ret;
    // 自身也算闭包一部分
    ret.insert(pt);

    if (pt.isEnd) return ret;

    // 队列中都不能出现已结束的taskMark
    std::queue<taskMark> qu;
    qu.push(pt);


    while (!qu.empty()) {
        taskMark temp = qu.front();
        qu.pop();

        // 取出First的Value
        Value tempValue = getFirstValueFromTaskMark(temp, tl);

        for (int i = 0; i < tl.tasklist.size(); i++) {
            if (tempValue == tl.tasklist[i].leftChar) {
                taskMark newTaskMark(i, 0);
                // 若已存在此taskMark 则不处理 继续
                if (ret.find(newTaskMark) == ret.end()) {
                    // 没找到 新建一个
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

    Node *startNode = new Node;                 // 创建起点
    taskMark tempTaskMark(0, 0);                // 创建起点的一个task
    if (isReduced(tempTaskMark, pt)) tempTaskMark.isEnd = true;
    startNode->taskSet.insert(tempTaskMark);    // 插入到tasklist
    closure_deal(startNode->taskSet, pt);       // 闭包扩展

    graph.nodeSet.insert(startNode);            // 每新建一个node都放入nodeSet
    graph.start = startNode;

    // 首先将队列初始化成S' -> S $
    // 然后计算此task的First的闭包
    // 生成完整的taskList
    // 然后处理taskList的First吸收集 用于产生下一个结点
    // 先逐个task产生一个tempNode 在已有set里查询是否已存在
    // 若结点存在 则产生边指向它
    // 若不存在 则新生成一个结点 并指向它
    // 并将结点放入待处理的队列Qu中
    // 当所有项目处理完后 完成一个循环
    // 每次循环都取出队列最前元素 并作处理
    // 先是闭包处理 然后逐个task处理
    //
    // 最后记得处理graph的start

    std::queue<Node*> qu;
    qu.push(startNode);     // 放入工作队列

    while (!qu.empty()) {   //处理每个队列中结点 空则处理完毕

        // 队列中取结点
        Node* tempNode = qu.front();
        qu.pop();

        cout << "取出的结点是" << endl;
        tempNode->disp(pt);

        /**********************************************
        // 对结点中已存在的tasks 用闭包函数求剩余task
        std::set<taskMark> tempClosureSet;
        for (const taskMark &x : tempNode->taskSet)
            for (const taskMark &y : closure(x, pt))
                tempClosureSet.insert(y);
        tempNode->taskSet = tempClosureSet;
        ***********************************************/

        // *************** 试验田 ******************
        std::map<Value, std::set<taskMark>> virtualMap;

        // 对于每一个task
        for (const taskMark &x : tempNode->taskSet) {

            if (x.isEnd) {
                tempNode->isReduced = true;
                cout << "已到末尾" << endl;
                continue;
            }

            Value tempValue = getFirstValueFromTaskMark(x, pt);     // 取出第一个值
            taskMark tempTMark(x.taskNum, x.index + 1);             // 生成新的taskMark
            if (isReduced(tempTMark, pt)) tempTMark.isEnd = true;   // 确定属性
            virtualMap[tempValue].insert(tempTMark);                // 插入到伪映射中
        }


        for (std::pair<const Value, std::set<taskMark>> &x : virtualMap) {

            closure_deal(x.second, pt);

            bool ok = false;
            for (Node* y : graph.nodeSet) {
                if (y->taskSet == x.second) {
                    cout << "已存在此结点ID = " << y->ID << " 现连接" << endl;
                    ok = true;
                    tempNode->edges[x.first] = y;
                }
            }

            if (!ok) {
                Node *tNode = new Node;
                tNode->taskSet = x.second;
                tempNode->edges[x.first] = tNode;
                cout << "新建结点ID = " << tNode->ID << endl;
                graph.nodeSet.insert(tNode);
                qu.push(tNode);
            }
        }







        // *************** 试验田 ******************

        /* *************** 暂时放弃 ****************
        // 逐个处理task
        for (const taskMark &x : tempNode->taskSet) {

            cout << "现在处理taskMark " ;
            x.disp(pt);

            // 先看是否为Reduced 是则继续处理下一条task
            if (x.isEnd) {
                tempNode->isReduced = true;
                cout << "已到末尾" << endl;
                continue;
            }

            // 对结点中每个task 应先产生对应的边和对应的伪结点
            // 处理完后再对每个边和伪结点都进行变现
            // 若有结点已存在 则指向已存在那个
            // 不存在 则new一个结点

            std::map<Value, std::set<taskMark>> virtualMap;

            // 寻找是否已存在边
            Value tempValue = getFirstValueFromTaskMark(x, pt);
            if (virtualMap.find(tempValue) != virtualMap.end())
                cout << "已存在此边" << endl;
            taskMark tempTMark(x.taskNum, x.index + 1);
            if (isReduced(tempTMark, pt)) tempTMark.isEnd = true;
            virtualMap[tempValue].insert(tempTMark);

            // 处理virtualMap 即变现
            for (std::pair<const Value, std::set<taskMark>> &y : virtualMap) {
                bool ok = false;
                for (Node* z : graph.nodeSet) {
                    if (z->taskSet == y.second) {
                        cout << "已存在此结点 现连接" << endl;
                        ok = true;
                        tempNode->edges[y.first] = z;
                    }
                }
                if (!ok) {
                    Node *tNode = new Node;
                    tNode->taskSet = y.second;
                    tempNode->edges[y.first] = tNode;
                    cout << "新建结点ID = " << tNode->ID << endl;
                    graph.nodeSet.insert(tNode);
                    qu.push(tNode);
                }
            }
        }
        *************** 暂时放弃 *****************/
    }
    return graph;
}
/* ******************* 这个暂时没成功 丢弃 *****************************

            // 寻找是否已存在边
            Value tempValue = getFirstValueFromTaskMark(x, pt);
            Node *tNode = NULL;
            if (tempNode->edges.find(tempValue) == tempNode->edges.end()) {
                // 没找到 再找找是否已经存在这个点

                tempNode->edges[tempValue] = tNode;
                tNode = new Node;
            } else {
                // 已存在 取这个点
                tNode = tempNode->edges[tempValue];
            }
            // 插入产生这点的对应的task
            taskMark temptaskmark(x.taskNum, x.index + 1);
            tNode.taskSet.insert(temptaskmark);
********************************************************************** */








// ******************** //
// *****建立项目集***** //
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
        cout << "错误！" << endl;
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

    // 分析：
    // 每个语句开头都是NonTerminal Char
    // 然后是冒号':'
    // 然后是字母或用单引号引起的字符
    // 小写字母和字符都是终结Terminal
    // 有'|'或符号
    // 分号结束
    // 分号开头则表示全文结束

    taskList retList;

    // 对于每一句

    while (true) {
        char c = 0;
        task retTask;

        // 排除空格
        while (isspace(c = getchar()));
        cout << "第一个字符为" << c << endl;
        if (!isalpha(c)) break; // 如果语句中第一个非空格字符不是字母 则结束循环 如';'

        // 已确认第一个为字母 吸收第一个NonTerminal Token
        Value tempValue(c, false);
        while (isalpha(c = getchar()))
            tempValue.s += c;
        retTask.leftChar = tempValue;   // 放入成左值 S -> ...

        // 吸收冒号
        while (isspace(c)) c = getchar();
        if (c != ':') {
            string temps = "expected \':\' but \' ";
            temps += c;
            temps += "\' ";
            throw temps;
        }

        // 已确认为冒号
        c = getchar();
        while (true) {          // 处理每个右值
            while (isspace(c)) c = getchar();

            if (c == '\'') {            // 单个字符'c'
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
            } else if (isalpha(c)) {      // 字符串
                Value tempV(c, false);
                while (isalpha(c = getchar()))
                    tempV.s += c;
                retTask.rchar.push_back(tempV);
                continue;
            } else if (c == '|') {
                // 先按正常流程结束
                retList.tasklist.push_back(retTask);
                // 清空右值 保留左值
                retTask.rchar.clear();
                // 继续
            } else if (c == ';'){
                cout << "完成一条语句输入" << endl;
                // 判断语句是否合法
                if (!isValidTask(retTask)) {
                    cout << "语句不合法" << endl;
                    throw "Invalid Syntax";
                }
                break;
            } else {
                cout << "内容不正常 为字符" << c << " 继续执行下一条语句输入" << endl;
                break;
            }
            c = getchar();
        }
        cout << "加入的task为" << retTask << endl;
        retList.tasklist.push_back(retTask);    // 放入处理完的一个task
    }
    return retList;
}

bool isValidTask(const task &pt) {
    // 判断形如 S : T '+' B ; 语句是否合法
    return pt.rchar.size() != 0 && pt.leftChar.s.length() > 0;
}




// ******************** //
// *****建立跳转表***** //
// ******************** //

/*********** 表格形式 ************
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
        // 逐个结点操作
        Node* tempNode = nodes[i];
        int state = tempNode->ID;
        cout << "现处理ID = " << state << endl;

        // 对边操作
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
            // 移进-归约 冲突
            cout << "!!!!!!!!!!!!!!!!移进-归约 冲突!!!!!!!!!!!!!!!!!!" << endl;
            std::set<Value> followS;
            std::vector<std::set<Value>> followRvector, tempFollowSet;
            // 对task操作
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
                cout << "出现conflict！" << endl;
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
            // 归约
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
