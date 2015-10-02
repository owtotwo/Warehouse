#! usr/bin/env python3
#-*- coding:utf-8 -*-
__author__ = 'AT'

from os import system
from copy import *

STOP = True
BACK = False

'''
    解数独，输入内容直接解，需要判断内容是否充足
    思路：
        对每个零进行替换成1-9
        重点在于相同的数如何进行删除
'''

def str_to_list(s):
    #将“300094010”这样的输入转换为单个数字的数组[3,0,0,0,9,4,0,1,0]
    return list(int(x) for x in str(s))

def sudo_print(ss):
    #显示好看点
    print("_______________________________________________")
    for i in range(9):
        for j in range(9):
            print(ss[i][j],end="  ")
            if (j+1)%3==0:
                print(" ",end=" ")
        print()
        if i==2 or i==5:
            print()
    print("-----------------------------------------------")
    print()

def plan(ss):
    for i in range(9):
        for j in range(9):
            ss[i][j] = [ss[i][j],]
    return ss

def swap(ss):
    #将0换成1-9
    for i in range(9):
        for j in range(9):
            if ss[i][j]==[0,]:
                ss[i][j] = list(range(1,10))
    return ss

def double(ss):
    #先处理行
    for i in range(9):
        ha = []
        for j in range(9):
            if len(ss[i][j])==1:
                ha.append(ss[i][j][0])
        if len(ha)!=len(set(ha)):
            return True
    #再处理列
    for i in range(9):
        ha = []
        for j in range(9):
            if len(ss[j][i])==1:
                ha.append(ss[j][i][0])
        if len(ha)!=len(set(ha)):
            return True
    #再处理中方格
    for i in range(0,9,3):
        for j in range(0,9,3):
            ha = []
            for x in range(3):
                for y in range(3):
                    if len(ss[x+i][y+j])==1:
                        ha.append(ss[x+i][y+j][0])
            if len(ha)!=len(set(ha)):
                return True
    return False

def handle(ss):
    global STOP
    #输入一行？先试试处理相同数
    for x in range(9):
        #mark = [i for i in ss[x] if isinstance(i,int)]
        mark = [i for i in ss[x] if len(i)==1]
        #print("mark内容是：",mark)
        #mark用于记录已出现数字
        for i in range(9):
            #if isinstance(ss[x][i],list):
            if len(ss[x][i])!=1:
                for j in mark:
                    try:
                        ss[x][i].remove(j[0])
                    except ValueError:
                        pass
                if len(ss[x][i])==1:
                    #print("在行被处理( %d,%d )"%(x+1,i+1))
                    STOP = False

    for y in range(9):
        line = [ss[t][y] for t in range(9)]
        #mark = [t for t in line if isinstance(t,int)]
        mark = [t for t in line if len(t)==1]
        #print("mark:",mark)
        for i in range(9):
            #if isinstance(ss[i][y],list):
             if len(ss[i][y])!=1:
                for j in mark:
                    try:
                        ss[i][y].remove(j[0])
                    except ValueError:
                        pass
                if len(ss[i][y])==1:
                    #print("在列被处理( %d,%d )"%(i+1,y+1))
                    STOP = False
    return  ss

def cube(ss):
    global STOP
    #处理3x3的中方格
    for x in range(0,9,3):
        #print("\n\n【%d行】"%(x+1))
        for y in range(0,9,3):
            #print("\n【%d列】"%(y+1))
            cu = []

            for s in range(3):
                for t in range(3):
                    cu.append(ss[x+s][y+t])
            #print("一个cube内容为：",cu)
            mark = list(filter(lambda n:len(n)==1,cu))
            #print("mark的内容对应cube(%d,%d)："%(x,y),mark)
            for s in range(3):
                for t in range(3):
                    if len(ss[x+s][y+t])!=1:
                        #print("每个要处理的ss[x+s][y+t] == ",ss[x+s][y+t])
                        for z in mark:
                            try:
                                ss[x+s][y+t].remove(z[0])
                            except ValueError:
                                pass
                        if len(ss[x+s][y+t])==1:
                            #print("在中方格被处理( %d ,%d )"%((x+s+1),(y+t+1)))
                            STOP = False
                        #print("处理完后的ss[x+s][y+t] == ",ss[x+s][y+t])
    return ss

def random_set(ss,p):
    #讲两个待定数的格子随便定一个数,返回选定的数
    temp = deepcopy(ss)
    for i in range(9):
        for j in range(9):
            if len(temp[i][j])==2:
                fit = temp[i][j]
                temp[i][j] = [temp[i][j][p],]
                #print(fit)
                #print("对格子( %d,%d )随便选"%(i,j))
                #print("内容为",fit,"选了%s"%temp[i][j])
                return temp
    return False

def is_finish(ss):
    for i in range(9):
        for j in range(9):
            if len(ss[i][j])!=1:
                return False
    return True

def is_empty(ss):
    for i in range(9):
        for j in range(9):
            if len(ss[i][j])==0:
                #print("空掉了！")
                BACK = True
                return True
    return False


def sudo_ui():
    #主要界面
    #大致内容为：先输入内容，按照每格以list方式存储，0则未解
    #输入内容比较多，ui暂时不会用，怎么办呢
    print("**************************************************************")
    print("***           The  Sudoku  Solution     —— By. AT        ***")
    print("**************************************************************")
    print("Hello! You can solve the sudoku problem in this progrem.\n")
    print("Ps: zero means empty, i.e. input the '300209001' (nine numbers for each row,and input nine rows)")
    row = []
    for i in range(9):
        while True:
            temp = input("row%d : "%(i+1))
            if temp.isdigit() and len(temp)==9:
                row.append(temp)
                break
            print("Wrong input(Perhaps the form is invail...do it again)")
    print("OK!")
    deal = list(map(str_to_list,row))
    deal = plan(deal)
    sudo_print(deal)
    swap(deal)
    system("pause")
    print("The solution is ......")
    sol = dp(deal)
    if sol==False:
        print("eh......it seems to fail...")
    else:
        sudo_print(sol)
        print("Bingo！")
    system("pause")

def dp(ss):
    global STOP,BACK
    STOP = True
    while not is_finish(ss):
        handle(ss)
        cube(ss)
        #sudo_print(ss)
        if BACK==True:
            if is_empty(ss) or double(ss):
                return False
        if STOP==True:
            #print("无解了好像")
            #system("pause")
            STOP = False
            BACK = True
            fuc = random_set(ss,0)
            #print("接下来要随机0——")
            #sudo_print(fuc)
            wait = dp(fuc)
            if wait==False:
                #print("这个随机是错的")
                #system("pause")
                fucl = random_set(ss,1)
                #print("接下来要随机1——")
                #sudo_print(fucl)
                wait1 = dp(fucl)
                if wait1==False:
                    #print("还是有问题啊")
                    #system("pause")
                    return False
                else:
                    return wait1
            else:
                #print("有结果了？")
                #sudo_print(wait)
                return wait
        STOP = True
    return ss
        #system("pause")


if __name__=='__main__':
    sudo_ui()

