from sys import *
import threading

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 27)


def main():
    def dfs(node):
        for i in range(len(availableWays[node])):
            updNode = availableWays[node][i]
            if infoAboutNodes[updNode] == -1:
                dfs(updNode)
        for i in range(len(availableWays[node])):
            infoAboutNodes[node] = max(infoAboutNodes[node], (infoAboutNodes[availableWays[node][i]] + 1) % 2)
        if infoAboutNodes[node] == -1:
            infoAboutNodes[node] = 0  # if there aren`t any moves from node, first player always wins

    fin = open("game.in", "r")
    fout = open("game.out", "w")

    numOfNodes, lines, start = [int(x) for x in fin.readline().split()]
    availableWays = [[] for _ in range(numOfNodes)]
    infoAboutNodes = [-1 for _ in range(numOfNodes)]  # None - didn`t attend node, 1 - first player, 0 - second %2

    for i in range(lines):
        startNode, endNode = [int(x) for x in fin.readline().split()]
        availableWays[startNode - 1].append(endNode - 1)

    dfs(start-1)
    if infoAboutNodes[start-1] != 0:
        print("First player wins", file=fout)
    else:
        print("Second player wins", file=fout)


thread = threading.Thread(target=main)
thread.start()
