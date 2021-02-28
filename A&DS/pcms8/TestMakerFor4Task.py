from random import *

fout = open("pathbge1.in", "w")
n = 50
m = 138
print(n, m, file=fout)
for i in range(m):
    a = randint(1, n)
    b = randint(1, n)
    print(a, b, file=fout)