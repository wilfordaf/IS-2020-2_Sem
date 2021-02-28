fin = open("input.txt", "r")
fout = open("output.txt", "w")

matrixsize = int(fin.readline())
matrix = [0] * matrixsize

for i in range(matrixsize):
    matrix[i] = [int(x) for x in fin.readline().split()]

bool = True
for i in range(matrixsize):
    for j in range(matrixsize):
        if matrix[i][j] != matrix[j][i]:
            bool = False
        if i == j and matrix[i][j] == 1:
            bool = False

if bool:
    print("YES", file=fout)
else:
    print("NO", file=fout)