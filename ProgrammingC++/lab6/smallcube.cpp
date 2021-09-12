#include "smallcube.h"

Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(float x_, float y_, float z_)
{
    x = x_;
    y = y_;
    z = z_;
};

float Point::getX() const
{
    return x;
}

float Point::getY() const
{
    return y;
}

float Point::getZ() const
{
    return z;
}

SmallCube::SmallCube(Point center_)
{
    center = center_;
    // colors = {'w', 'y', 'b', 'g', 'r', 'o'};
    colors = {'0', '0', '0', '0', '0', '0'};
    if (center.getX() < 0)
    {
        colors[2] = 'b';
    }
    else if (center.getX() > 0)
    {
        colors[3] = 'g';
    }
    if (center.getY() < 0)
    {
        colors[5] = 'o';
    }
    else if (center.getY() > 0)
    {
        colors[4] = 'r';
    }
    if (center.getZ() < 0)
    {
        colors[1] = 'y';
    }
    else if (center.getZ() > 0)
    {
        colors[0] = 'w';
    }
}

SmallCube::SmallCube()
{
    center = Point();
    colors = {'w', 'y', 'b', 'g', 'r', 'o'};
}

std::vector<char>& SmallCube::getColors()
{
    return colors;
}

void SmallCube::setColors(std::vector<char>& newColors)
{
    colors = newColors;
}

void SmallCube::drawCube()
{
    std::vector<float> sideColor;

	glBegin(GL_QUADS);

	// front
	sideColor = charToColor(colors[0]);
	glColor3f(sideColor[0], sideColor[1], sideColor[2]);
	glVertex3f(center.getX() - 0.5, center.getY() - 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() - 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() + 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() + 0.5, center.getZ() + 0.5);

	// back
	sideColor = charToColor(colors[1]);
	glColor3f(sideColor[0], sideColor[1], sideColor[2]);
	glVertex3f(center.getX() - 0.5, center.getY() - 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() + 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() + 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() - 0.5, center.getZ() - 0.5);

	// left
	sideColor = charToColor(colors[2]);
	glColor3f(sideColor[0], sideColor[1], sideColor[2]);
	glVertex3f(center.getX() - 0.5, center.getY() - 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() + 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() + 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() - 0.5, center.getZ() - 0.5);

	// right
	sideColor = charToColor(colors[3]);
	glColor3f(sideColor[0], sideColor[1], sideColor[2]);
	glVertex3f(center.getX() + 0.5, center.getY() - 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() + 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() + 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() - 0.5, center.getZ() + 0.5);

	// top
	sideColor = charToColor(colors[4]);
	glColor3f(sideColor[0], sideColor[1], sideColor[2]);
	glVertex3f(center.getX() - 0.5, center.getY() + 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() + 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() + 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() + 0.5, center.getZ() - 0.5);

	// bot
	sideColor = charToColor(colors[5]);
	glColor3f(sideColor[0], sideColor[1], sideColor[2]);
	glVertex3f(center.getX() - 0.5, center.getY() - 0.5, center.getZ() + 0.5);
	glVertex3f(center.getX() - 0.5, center.getY() - 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() - 0.5, center.getZ() - 0.5);
	glVertex3f(center.getX() + 0.5, center.getY() - 0.5, center.getZ() + 0.5);
	glEnd();
}


void SmallCube::turnLeft()
{
    char temp = colors[0];
    colors[0] = colors[3];
    colors[3] = colors[1];
    colors[1] = colors[2];
    colors[2] = temp;
}

void SmallCube::turnRight()
{
    char temp = colors[0];
    colors[0] = colors[2];
    colors[2] = colors[1];
    colors[1] = colors[3];
    colors[3] = temp;
}

void SmallCube::turnUp()
{
    char temp = colors[0];
    colors[0] = colors[4];
    colors[4] = colors[1];
    colors[1] = colors[5];
    colors[5] = temp;
}

void SmallCube::turnDown()
{
    char temp = colors[0];
    colors[0] = colors[5];
    colors[5] = colors[1];
    colors[1] = colors[4];
    colors[4] = temp;
}

void SmallCube::turnClockwise()
{
    char temp = colors[2];
    colors[2] = colors[4];
    colors[4] = colors[3];
    colors[3] = colors[5];
    colors[5] = temp;
}

void SmallCube::turnAntiClockwise()
{
    char temp = colors[2];
    colors[2] = colors[5];
    colors[5] = colors[3];
    colors[3] = colors[4];
    colors[4] = temp;
}

char SmallCube::operator[](std::string side) const
{
    switch (side[0])
    {
    case 't':
        return colors[4];
    case 'b':
        switch (side[1])
        {
        case 'o':
            return colors[5];
        case 'a':
            return colors[1];
        }
    case 'f':
        return colors[0];

    case 'l':
        return colors[2];
    case 'r':
        return colors[3];
    }
    return '0';
}

bool SmallCube::checkColor(char c) const
{
    for (char color : colors)
    {
        if (color == c)
        {
            return true;
        }
    }
    return false;
}
std::vector<float> charToColor(const char ch)
{
    switch (ch)
    {
    case 'r':
        {
        std::vector<float> r = {1.0, 0.0, 0.0};
        return r;
        }

    case 'w':
        {
        std::vector<float> w = {1.0, 1.0, 1.0};
        return w;
        }

    case 'y':
        {
        std::vector<float> y = {1.0, 1.0, 0.0};
        return y;
        }

    case 'b':
        {
        std::vector<float> b = {0.0, 0.0, 1.0};
        return b;
        }

    case 'o':
        {
        std::vector<float> o = {1.0, 0.5, 0.0};
        return o;
        }

    case 'g':
        {
        std::vector<float> g = {0.0, 1.0, 0.0};
        return g;
        }
    case '0':
        std::vector<float> black = {0.0, 0.0, 0.0};
        return black;
    }
    return {};
}
