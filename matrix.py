#！usr/bin/evn python3
# -*- coding: utf-8 -*-
__author__ = 'AT'

'''This is a little python program used to calculate the matrix.
   The main idea is using the list to store the number...'''

from fractions import Fraction

OPEN_PROCESS_VIEW = False

def str_to_list(s):
    #string-------->list
    #input a list number which used space to be interval
    #eq:str = "1 2 14 3 9",expected to change to a list [1,2,14,3,9]
    #clean the whitespace from the beginning and the end
    return list(map(int,s.strip().split(' ')))

def is_all_zero(s):
    #list-------->bool
    #use to judge if it is all zero
    for i in s:
        if i!=0:
            return False
    return True

def pivot_pos(s):
    #list-------->int
    #return the pos of leading element
    for i in range(len(s)):
        if s[i]!=0:
            return i
    return None

def get_pivot_pos(s):
    for i in range(len(s)):
        if s[i]!=0:
            return i
    #return a number which is enough big
    return 1000

def zero_below(ss):
    #sink the all-zero row
    #return the new zero below matrix
    tail = []
    i = 0
    while i<len(ss):
        if is_all_zero(ss[i]):
            tail.append(ss[i])
            del ss[i]
        else:
            i += 1
    ss += tail
    return ss

def is_all_zero_below(ss):
    #judge if all zero-row are below
    mark_i = 0
    for i in range(len(ss)):
        if is_all_zero(ss[i]):
            mark_i = i
            break
    for i in range(mark_i+1,len(ss)):
        if not is_all_zero(ss[i]):
            return False
    return True

def is_non_solution(s):
    #judge if it is non-solution
    if is_all_zero(s[:-1]) and s[-1]!=0:
        return True
    return False

def is_row_echelon_form(ss):
    #all nonzero row are above any row of all zero
    #the pivot is left of the below pivot
    if not is_all_zero_below(ss):
        return False
    pivot_list = list(map(pivot_pos,ss))
    #print(pivot_list)
    for i in range(len(pivot_list)-1):
        if pivot_list[i+1]!=None and pivot_list[i]>=pivot_list[i+1]:
            #print("It is not row echelon form")
            return False
    #print("Yes it is row echelon form")
    return True

def is_std_echelon_matrix(ss):
    if not is_row_echelon_form(ss):
        return False
    for i in range(len(ss)):
        if not is_all_zero(ss[i]):
            first = pivot_pos(ss[i])
            for j in range(len(ss)):
                if ss[j][first]!=0 and j!=i:
                    return False
    return True


def matrix_sort(ss):
    #arrange the matrix
    return sorted(ss,key=get_pivot_pos)

def matrix_print(ss):
    #list(list)-------->display
    print("Matrix:-------------------")
    for i in ss:
        print(' ',i)
    print("--------------------------")

def all_print(ss):
    print("-------------------------------------------")
    for i in ss:
        for j in i:
            print("%6s"%j,end="   ")
        print()
    print("-------------------------------------------")

def deal(ss,pos=0):
    #首先第一行的数pivot系数为1，然后处理下面的所有
    #zero_below(ss)
    if pos>=len(ss):
        print("完成任务！")
        is_row_echelon_form(ss)
        return ss
    if is_all_zero(ss[pos]):
        #print("因首行全零而结束！")
        return ss
    if is_non_solution(ss[pos]):
        print("无解！")
        return ss
    #print("进行化简过程：")
    #all_print(ss)
    for i in ss[pos]:
        if i!=0:
            coe = i
            break
    #coe is coeffcient
    ss[pos] = list(Fraction(x,coe) for x in ss[pos])
    #"first" row is change(the leading element is '1' now)
    #print("同除后首列内容为：")
    #all_print([ss[pos],])

    first = pivot_pos(ss[pos])
    for i in range(pos+1,len(ss)):
        if ss[i][first]!=0:
            coe1 = ss[i][first]
            ss[i] = list(x*Fraction(-1,coe1) for x in ss[i])
            for j in range(len(ss[pos])):
                ss[i][j] += ss[pos][j]
    #递归
    #print("简化完毕，下一步排序整理：")
    #all_print(ss)
    ss = matrix_sort(ss)
    #print("排序整理后：")
    #all_print(ss)
    if OPEN_PROCESS_VIEW:
        print("Step:")
        all_print(ss)
    ss = deal(ss,pos+1)
    return ss
    #now the first row is dealing over



def get_solution(ss):
    ss = ss[::-1]
    for i in range(len(ss)-1):
        if not is_all_zero(ss[i]):
            first = pivot_pos(ss[i])
            for j in range(i,len(ss)-1):
                if ss[j+1][first]!=0:
                    temp = list(ss[j+1][first]*(-1)*x for x in ss[i])
                    for k in range(len(ss[j+1])):
                        ss[j+1][k] += temp[k]
                    #ss[j+1] += list(ss[j+1][first]*Fraction(-1,ss[i][first])*x for x in ss[j])
    return ss[::-1]

def has_solution(ss):
    for i in ss:
        if is_non_solution(i):
            return False
    return True

def matrix_is_vaild(ss):
    #check the matrix is matrix or not
    if len(ss)==1:
        return True
    for i in range(len(ss)-1):
        if len(ss[i])!=len(ss[i+1]):
            return False
    return True

def solve(ss):
    print("初步得出：")
    ss = matrix_sort(ss)
    ss = deal(ss)
    if OPEN_PROCESS_VIEW==True:
        print("\n\n处理完毕：")
    all_print(ss)
    if not has_solution(ss):
        print("【无解！】")
        return False
    print("【有解！】")
    print("\n\t经过化简......\n")
    print("【最终解】为：")
    if not is_std_echelon_matrix(ss):
        ss = get_solution(ss)
        all_print(ss)
        print("*************** That's all ****************")
    return True

def matrix_ui():

    ss = []
    row = 0
    print()
    print("Please enter the row of the matrix:")
    print("\t(Ps : An empty row input means over, and input 'over' will shut down the program.)\n")
    while True:
        row += 1
        s = input("row %d :"%row)
        if s.lower()=="over":
            return False
        if s=="":
            print("OK!")
            break
        try:
            ss.append(str_to_list(s))
        except ValueError as err1:
            print("What you input are in a wrong form(such as the alpha and so on).")
            print("Enter again!")
        if not matrix_is_vaild(ss):
            print("The form of this row is invaild, please input again...")
            ss.pop()
            row -= 1
    print("【The matrix】 is:")
    all_print(ss)
    print("【The solution】 is:")
    solve(ss)
    return True





def start():
    global OPEN_PROCESS_VIEW
    print("**************************************************************")
    print("***       The Matrix Equation Solution     —— By. AT     ***")
    print("**************************************************************")
    print("Hello! You can solve the matrix problem in this progrem.\n")
    yes_or_no = input("\tDo you want to open the process-view of solution?(y/n): ")
    if yes_or_no=='y':
        print("\tThe process-view is open...")
        OPEN_PROCESS_VIEW = True
    else:
        print("\tThe process-view is closed...")
    while matrix_ui():
        print("Continue...")
    print("Bye!~")

if __name__=="__main__":
    start()

'''
    OPEN_PROCESS_VIEW = True
    s1 = "0 -3 -6 4 9"
    s2 = "-1 -2 -1 3 1"
    s3 = "-2 -3 0 3 -1"
    s4 = "1 4 5 -9 -7"

    haha = list(map(str_to_list,[s1,s2,s3,s4]))

    print("内容符合？",matrix_is_vaild(haha))
    solve(haha)
'''