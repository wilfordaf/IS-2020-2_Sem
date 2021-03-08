from sys import *
import threading

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 27)


def main():
    class Node:
        def __init__(self, color, availableways):
            self.color = color
            self.availableways = availableways

        def getSize(self):
            return len(self.availableways)

    def dfs(node, lenPath):
        nonlocal wasAnswer
        infoAboutNodes[node].color = "GREY"
        if lenPath == numOfNodes:
            wasAnswer = True
            return True
        for i in range(infoAboutNodes[node].getSize()):
            newNode = infoAboutNodes[node].availableways[i]
            if infoAboutNodes[newNode].color == "WHITE":
                if dfs(newNode, lenPath + 1):
                    return True
        infoAboutNodes[node].color = "WHITE"

    fin = open("hamiltonian.in", "r")
    fout = open("hamiltonian.out", "w")

    numOfNodes, lines = [int(x) for x in fin.readline().split()]
    infoAboutNodes = [Node("WHITE", []) for _ in range(numOfNodes)]
    nodesWithoutIn = [i for i in range(0, numOfNodes)]
    wasAnswer = False

    for i in range(lines):
        startNode, endNode = [int(x) for x in fin.readline().split()]
        infoAboutNodes[startNode - 1].availableways.append(endNode - 1)
        try:
            nodesWithoutIn.remove(endNode - 1)
        except ValueError:
            pass

    dfs(nodesWithoutIn.pop(), 1)  # if there are >1 nodes without In, graph is undoubtedly not hamiltonian

    print("YES" if wasAnswer else "NO", file=fout)


thread = threading.Thread(target=main)
thread.start()