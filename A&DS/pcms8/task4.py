from sys import *
import threading

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 26)


def main():
    class Node:
        def __init__(self, group, availableways):
            self.availableways = availableways
            self.group = group

        def printnode(self):
            print(self.availableways, self.group)

    def dfs(node, congroup):
        node.group = congroup
        for i in range(len(node.availableways)):
            if infoaboutnodes[node.availableways[i]].group is None:
                dfs(infoaboutnodes[node.availableways[i]], congroup)

    fin = open("components.in", "r")
    fout = open("components.out", "w")

    matrixsize, lines = [int(x) for x in fin.readline().split()]
    infoaboutnodes = []

    for i in range(matrixsize):
        infoaboutnodes.append(Node(None, []))

    for i in range(lines):
        numofline, numofcol = [int(x) for x in fin.readline().split()]
        a = infoaboutnodes[numofline - 1].availableways
        b = infoaboutnodes[numofcol - 1].availableways
        if numofcol - 1 not in a:
            a.append(numofcol - 1)
        if numofline - 1 not in b:
            b.append(numofline - 1)

    cnt = 0
    for i in range(matrixsize):
        if infoaboutnodes[i].group is None:
            cnt += 1
            dfs(infoaboutnodes[i], cnt)

    print(cnt, file=fout)
    for node in infoaboutnodes:
        print(node.group, end=' ', file=fout)


thread = threading.Thread(target=main)
thread.start()
