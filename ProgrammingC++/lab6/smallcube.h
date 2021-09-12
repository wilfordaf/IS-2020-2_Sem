#ifndef SMALLCUBE_H
#define SMALLCUBE_H
#include <vector>
#include <GL/glut.h>
#include <iostream>

class Point{
private:
    float x, y, z;
public:
    Point();
    Point(float, float, float);
    float getX() const;
    float getY() const;
    float getZ() const;
};

class SmallCube
{
private:
    Point center;
    std::vector<char> colors;
public:
    SmallCube();
    SmallCube(Point);
    std::vector<char>& getColors();
    void setColors(std::vector<char>&);
    void drawCube();
    void turnLeft();
    void turnRight();
    void turnUp();
    void turnDown();
    void turnClockwise();
    void turnAntiClockwise();
    bool checkColor(char) const;
    char operator[](std::string) const;
};

std::vector<float> charToColor(const char);

#endif // SMALLCUBE_H
