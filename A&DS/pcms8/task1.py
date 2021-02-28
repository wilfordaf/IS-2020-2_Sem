fin = open("input.txt", "r")
fout = open("output.txt", "w")

matrixsize, lines = [int(x) for x in fin.readline().split()]
matrix = [[0] * matrixsize for i in range(matrixsize)]

for i in range(lines):
    numofline, numofcol = [int(x) for x in fin.readline().split()]
    matrix[numofline-1][numofcol-1] = 1

for i in range(matrixsize):
    for j in range(matrixsize):
        print(matrix[i][j], end=" ", file=fout)
    print("", file=fout)