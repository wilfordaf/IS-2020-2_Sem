from sys import *
import threading

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 26)


def main():
    fin = open("input.txt", "r")
    fout = open("output.txt", "w")

    matrixsize, lines = [int(x) for x in fin.readline().split()]

    labirynth = [[None for i in range(lines)] for j in range(matrixsize)]
    previousstep = [["" for i in range(lines)] for j in range(matrixsize)]
    distancetonode = [[-1 for i in range(lines)] for j in range(matrixsize)]

    startlabirynth = []
    goal = []
    queue = []
    finalpath = ""

    for i in range(matrixsize):
        line = fin.readline()
        for j in range(lines):
            if line[j] == "S":
                startlabirynth.append(i)
                startlabirynth.append(j)
                queue.append(startlabirynth)
                distancetonode[i][j] = 0
                labirynth[i][j] = True
            elif line[j] == "T":
                goal.append(i)
                goal.append(j)
                labirynth[i][j] = True
            elif line[j] == ".":
                labirynth[i][j] = True
            else:
                labirynth[i][j] = False

    while queue:
        currentnodey, currentnodex = queue.pop(0)
        if distancetonode[goal[0]][goal[1]] != -1:
            break
        if currentnodey > 0:
            if labirynth[currentnodey - 1][currentnodex] and distancetonode[currentnodey - 1][currentnodex] == -1:
                previousstep[currentnodey - 1][currentnodex] = "U"
                distancetonode[currentnodey - 1][currentnodex] = distancetonode[currentnodey][currentnodex] + 1
                queue.append([currentnodey - 1, currentnodex])
        if currentnodey < matrixsize - 1:
            if labirynth[currentnodey + 1][currentnodex] and distancetonode[currentnodey + 1][currentnodex] == -1:
                previousstep[currentnodey + 1][currentnodex] = "D"
                distancetonode[currentnodey + 1][currentnodex] = distancetonode[currentnodey][currentnodex] + 1
                queue.append([currentnodey + 1, currentnodex])
        if currentnodex > 0:
            if labirynth[currentnodey][currentnodex - 1] and distancetonode[currentnodey][currentnodex - 1] == -1:
                previousstep[currentnodey][currentnodex - 1] = "L"
                distancetonode[currentnodey][currentnodex - 1] = distancetonode[currentnodey][currentnodex] + 1
                queue.append([currentnodey, currentnodex - 1])
        if currentnodex < lines - 1:
            if labirynth[currentnodey][currentnodex + 1] and distancetonode[currentnodey][currentnodex + 1] == -1:
                previousstep[currentnodey][currentnodex + 1] = "R"
                distancetonode[currentnodey][currentnodex + 1] = distancetonode[currentnodey][currentnodex] + 1
                queue.append([currentnodey, currentnodex + 1])

    print(distancetonode[goal[0]][goal[1]], file=fout)
    if distancetonode[goal[0]][goal[1]] != -1:
        for i in range(distancetonode[goal[0]][goal[1]]):
            if previousstep[goal[0]][goal[1]] == "U":
                goal[0] += 1
                finalpath += "U"
            elif previousstep[goal[0]][goal[1]] == "D":
                goal[0] -= 1
                finalpath += "D"
            elif previousstep[goal[0]][goal[1]] == "L":
                goal[1] += 1
                finalpath += "L"
            elif previousstep[goal[0]][goal[1]] == "R":
                goal[1] -= 1
                finalpath += "R"
        print(finalpath[::-1], file=fout)


thread = threading.Thread(target=main)
thread.start()
