fin = open("input.txt", "r")
fout = open("output.txt", "w")

matrixsize, lines = [int(x) for x in fin.readline().split()]
matrix = [[0] * matrixsize for i in range(matrixsize)]

for i in range(lines):
    numofline, numofcol = [int(x) for x in fin.readline().split()]
    matrix[numofline-1][numofcol-1] += 1
    matrix[numofcol - 1][numofline - 1] += 1

bool = False
for i in range(matrixsize):
    for j in range(matrixsize):
        if matrix[i][j] > 1:
            bool = True

if bool:
    print("YES", file=fout)
else:
    print("NO", file=fout)