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
        answer.append(node + 1)
        infoAboutNodes[node].color = "GREY"
        nonlocal startOfCycle
        for i in range(infoAboutNodes[node].getSize()):
            newNode = infoAboutNodes[node].availableways[i]
            if infoAboutNodes[newNode].color == "WHITE":
                if dfs(newNode):
                    return True
            elif infoAboutNodes[newNode].color == "GREY":
                startOfCycle = newNode + 1
                return True

        infoAboutNodes[node].color = "BLACK"
        answer.pop()

    fin = open("cycle.in", "r")
    fout = open("cycle.out", "w")

    numOfNodes, lines = [int(x) for x in fin.readline().split()]
    infoAboutNodes = [Node("WHITE", []) for i in range(numOfNodes)]
    wasAnswer = False
    startOfCycle = 0
    answer = []

    for i in range(lines):
        startNode, endNode = [int(x) for x in fin.readline().split()]
        infoAboutNodes[startNode - 1].availableways.append(endNode - 1)

    for i in range(numOfNodes):
        if infoAboutNodes[i].color == "WHITE":
            if dfs(i):
                wasAnswer = True
                break

    if wasAnswer:
        print("YES", file=fout)
        print(*answer[answer.index(startOfCycle):len(answer)], file=fout)
    else:
        print("NO", file=fout)


thread = threading.Thread(target=main)
thread.start()
