from sys import *
import threading

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 27)


def main():
    class Node:
        def __init__(self, color, availableways):
            self.color = color
            self.availableways = availableways

        def printnode(self):
            print(self.availableways, self.color)

        def getSize(self):
            return len(self.availableways)

    def dfs(node):
        infoAboutNodes[node].color = "GREY"
        for i in range(infoAboutNodes[node].getSize()):
            newNode = infoAboutNodes[node].availableways[i]
            if infoAboutNodes[newNode].color == "WHITE":
                if dfs(newNode):
                    return True
            elif infoAboutNodes[newNode].color == "GREY":
                return True
        infoAboutNodes[node].color = "BLACK"
        answer.append(node + 1)

    fin = open("topsort.in", "r")
    fout = open("topsort.out", "w")

    numOfNodes, lines = [int(x) for x in fin.readline().split()]
    infoAboutNodes = [Node("WHITE", []) for i in range(numOfNodes)]
    answer = []
    wasAnswer = False

    for i in range(lines):
        startNode, endNode = [int(x) for x in fin.readline().split()]
        infoAboutNodes[startNode - 1].availableways.append(endNode - 1)

    for i in range(numOfNodes):
        if infoAboutNodes[i].color == "WHITE":
            if dfs(i):
                wasAnswer = True
                break
    if wasAnswer:
        print(-1, file=fout)
    else:
        print(*reversed(answer), file=fout)


thread = threading.Thread(target=main)
thread.start()