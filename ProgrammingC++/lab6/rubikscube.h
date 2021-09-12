#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H
#include <vector>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include "smallcube.h"

extern std::vector<std::string> randomActions;
extern std::vector<std::string> solveActions;
extern bool solveFlag;

class RubiksCube
{
private:
    std::vector<std::vector<std::vector<SmallCube>>> coordinates{3, std::vector<std::vector<SmallCube>>{3, std::vector<SmallCube>{3}}};
public:
    RubiksCube();
    void drawRubiksCube();
    int rotateCube(std::string);
    void printPosToFile(std::string);
    void getPosFromFile(std::string);
    void random();
    int yellowOnTop();
    int whiteFlower();
    int whiteCross();
    int whiteSide();
    int middleLayer();
    int yellowCross();
    int completeYellowCross();
    int topCorners();
    int finalStraight();
    void solve();
};


#endif // RUBIKSCUBE_H
