fin = open("pathbge1.in", "r")
fout = open("pathbge1.out", "w")

matrixsize, lines = [int(x) for x in fin.readline().split()]
availableways = []
minpath = [10**9 for i in range(matrixsize)]
minpath[0] = 0

for i in range(lines):
    numofline, numofcol = [int(x) for x in fin.readline().split()]
    availableways.append([numofline - 1, numofcol - 1])
    availableways.append([numofcol - 1, numofline - 1])

for i in range(matrixsize):
    bool = False
    for j in range(2*lines):
        if minpath[availableways[j][1]] > minpath[availableways[j][0]] + 1:
            minpath[availableways[j][1]] = minpath[availableways[j][0]] + 1
            bool = True
    if not bool:
        break

for i in range(matrixsize):
    print(minpath[i], end=' ', file=fout)