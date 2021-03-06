from sys import *
from random import *
import threading

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 27)


def main():
    class Node:
        def __init__(self, part, availableways):
            self.part = part  # 0 - node wasn`t attended yet, 1&2 - different parts
            self.availableways = availableways

        def getSize(self):
            return len(self.availableways)

    def returnOpposite(group):
        if group == 1:
            return 2
        elif group == 2:
            return 1

    def dfs(node, curPart):
        nonlocal wasAnswer
        infoAboutNodes[node].part = curPart
        for i in range(infoAboutNodes[node].getSize()):
            newNode = infoAboutNodes[node].availableways[i]
            if infoAboutNodes[newNode].part == 0:
                if dfs(newNode, returnOpposite(curPart)):
                    return True
            elif infoAboutNodes[newNode].part == curPart:
                wasAnswer = True
                return True

    fin = open("bipartite.in", "r")
    fout = open("bipartite.out", "w")

    numOfNodes, lines = [int(x) for x in fin.readline().split()]
    infoAboutNodes = [Node(0, []) for i in range(numOfNodes)]
    wasAnswer = False

    for i in range(lines):
        startNode, endNode = [int(x) for x in fin.readline().split()]
        infoAboutNodes[startNode - 1].availableways.append(endNode - 1)
        infoAboutNodes[endNode - 1].availableways.append(startNode - 1)

    for i in range(numOfNodes):
        if infoAboutNodes[i].part == 0:
            if dfs(i, randint(1, 2)):
                break

    print("NO" if wasAnswer else "YES", file=fout)


thread = threading.Thread(target=main)
thread.start()
