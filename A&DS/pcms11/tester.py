import os
import sys
from random import *

fin_my = open("path.out", "r")
fin_other = open("path_other.out", "r")

#  this is complete tester to fix D task in 11 lab
#  ofc you can replace several randints and rebuild this tester any other every task
#  compile your solution and replace "your_program_name.exe"
#  then compile mine task4.cpp and start checking
#  dont forget to create all the files mentioned in the code
#  good luck in your studies <3


def solve():
    fout = open("path.in", "w")
    n, m = 60, 2000
    s = randint(1, n)

    print(n, m, s, file=fout)
    for i in range(m):
        v1, v2, w = randint(1, n), randint(1, n), randint(-10 ** 15, 10 ** 15)
        print(v1, v2, w, file=fout)

    os.system('"C:/Folder_where_is_my_program/task4.exe"')
    os.system('"C:/Folder_where_is_your_program/your_program_name.exe"')

    for line in fin_my:
        my_line = line.split()
        wilfordaf_line = fin_other.readline().split()
        if my_line != wilfordaf_line:
            print("Wrong answer!")
            print("My:", my_line, "Correct:", wilfordaf_line)
            sys.exit(-1)
    fout.close()


for attempt in range(100):
    print("Attempt №", attempt + 1)
    solve()
    print("Passed Correctly!")
