import os
import sys
from random import *

fin_my = open("path.out", "r")
fin_other = open("path1.out", "r")


def solve():
    fout = open("path.in", "w")
    n, m = 60, 2000
    s = randint(1, n)

    print(n, m, s, file=fout)
    for i in range(m):
        v1, v2, w = randint(1, n), randint(1, n), randint(-10**15, 10 ** 15)
        print(v1, v2, w, file=fout)

    os.system('"D:/ITMO/2 semester/ProgrammingC++/Learningcpp/task411/s4hack.exe"')
    os.system('"D:/ITMO/2 semester/ProgrammingC++/Learningcpp/task411/main.exe"')

    for line in fin_my:
        my_line = line.split()
        s4hack_line = fin_other.readline().split()
        if my_line != s4hack_line:
            print("Wrong answer!")
            print("My:", my_line, "Correct:", s4hack_line)
            sys.exit(-1)

    fout.close()


for attempt in range(100):
    print("Attempt №", attempt + 1)
    solve()
    print("Passed Correctly!")
