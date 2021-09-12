#include "rubikscube.h"

RubiksCube::RubiksCube()
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                float a = i, b = j, c = k;
                if (a < 0)
                {
                    a -= 0.05;
                }
                else if (a > 0)
                {
                    a += 0.05;
                }
                if (b < 0)
                {
                    b -= 0.05;
                }
                else if (b > 0)
                {
                    b += 0.05;
                }
                if (c < 0)
                {
                    c -= 0.05;
                }
                else if (c > 0)
                {
                    c += 0.05;
                }
                coordinates[i + 1][j + 1][k + 1] = SmallCube(Point(a, b, c));
            }
        }
    }
}

void RubiksCube::drawRubiksCube()
{
    for (auto x : coordinates)
    {
        for (auto y : x)
        {
            for (SmallCube c : y)
            {
                c.drawCube();
            }
        }
    }
}

int RubiksCube::rotateCube(std::string order)
{
    int layer;
    if (order == "U" || order == "D'" || order == "ML")
    {
        if (order == "U")
        {
            layer = 2;
        }
        else if (order == "ML")
        {
            layer = 1;
        }
        else
        {
            layer = 0;
        }
        std::vector<char> temp = coordinates[0][layer][0].getColors();
        coordinates[0][layer][0].setColors(coordinates[0][layer][2].getColors());
        coordinates[0][layer][2].setColors(coordinates[2][layer][2].getColors());
        coordinates[2][layer][2].setColors(coordinates[2][layer][0].getColors());
        coordinates[2][layer][0].setColors(temp);
        temp = coordinates[1][layer][0].getColors();
        coordinates[1][layer][0].setColors(coordinates[0][layer][1].getColors());
        coordinates[0][layer][1].setColors(coordinates[1][layer][2].getColors());
        coordinates[1][layer][2].setColors(coordinates[2][layer][1].getColors());
        coordinates[2][layer][1].setColors(temp);
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                coordinates[i][layer][j].turnLeft();
            }
        }
    }
    else if (order == "U'" || order == "D" || order == "MR")
    {
        if (order == "U'")
        {
            layer = 2;
        }
        else if (order == "MR")
        {
            layer = 1;
        }
        else
        {
            layer = 0;
        }
        std::vector<char> temp = coordinates[0][layer][0].getColors();
        coordinates[0][layer][0].setColors(coordinates[2][layer][0].getColors());
        coordinates[2][layer][0].setColors(coordinates[2][layer][2].getColors());
        coordinates[2][layer][2].setColors(coordinates[0][layer][2].getColors());
        coordinates[0][layer][2].setColors(temp);
        temp = coordinates[1][layer][0].getColors();
        coordinates[1][layer][0].setColors(coordinates[2][layer][1].getColors());
        coordinates[2][layer][1].setColors(coordinates[1][layer][2].getColors());
        coordinates[1][layer][2].setColors(coordinates[0][layer][1].getColors());
        coordinates[0][layer][1].setColors(temp);
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                coordinates[i][layer][j].turnRight();
            }
        }
    }
    else if (order == "R" || order == "L'" || order == "MAC")
    {
        if (order == "R")
        {
            layer = 2;
        }
        else if (order == "MAC")
        {
            layer = 1;
        }
        else
        {
            layer = 0;
        }
        std::vector<char> temp = coordinates[0][0][layer].getColors();
        coordinates[0][0][layer].setColors(coordinates[2][0][layer].getColors());
        coordinates[2][0][layer].setColors(coordinates[2][2][layer].getColors());
        coordinates[2][2][layer].setColors(coordinates[0][2][layer].getColors());
        coordinates[0][2][layer].setColors(temp);
        temp = coordinates[0][1][layer].getColors();
        coordinates[0][1][layer].setColors(coordinates[1][0][layer].getColors());
        coordinates[1][0][layer].setColors(coordinates[2][1][layer].getColors());
        coordinates[2][1][layer].setColors(coordinates[1][2][layer].getColors());
        coordinates[1][2][layer].setColors(temp);
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                coordinates[i][j][layer].turnAntiClockwise();
            }
        }
    }
    else if (order == "R'" || order == "L" || order == "MC")
    {
        if (order == "R'")
        {
            layer = 2;
        }
        else if (order == "MC")
        {
            layer = 1;
        }
        else
        {
            layer = 0;
        }
        std::vector<char> temp = coordinates[0][0][layer].getColors();
        coordinates[0][0][layer].setColors(coordinates[0][2][layer].getColors());
        coordinates[0][2][layer].setColors(coordinates[2][2][layer].getColors());
        coordinates[2][2][layer].setColors(coordinates[2][0][layer].getColors());
        coordinates[2][0][layer].setColors(temp);
        temp = coordinates[0][1][layer].getColors();
        coordinates[0][1][layer].setColors(coordinates[1][2][layer].getColors());
        coordinates[1][2][layer].setColors(coordinates[2][1][layer].getColors());
        coordinates[2][1][layer].setColors(coordinates[1][0][layer].getColors());
        coordinates[1][0][layer].setColors(temp);
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                coordinates[i][j][layer].turnClockwise();
            }
        }
    }
    else if (order == "F" || order == "B'" || order == "MU")
    {
        if (order == "B'")
        {
            layer = 2;
        }
        else if (order == "MU")
        {
            layer = 1;
        }
        else
        {
            layer = 0;
        }
        std::vector<char> temp = coordinates[layer][0][0].getColors();
        coordinates[layer][0][0].setColors(coordinates[layer][0][2].getColors());
        coordinates[layer][0][2].setColors(coordinates[layer][2][2].getColors());
        coordinates[layer][2][2].setColors(coordinates[layer][2][0].getColors());
        coordinates[layer][2][0].setColors(temp);
        temp = coordinates[layer][1][0].getColors();
        coordinates[layer][1][0].setColors(coordinates[layer][0][1].getColors());
        coordinates[layer][0][1].setColors(coordinates[layer][1][2].getColors());
        coordinates[layer][1][2].setColors(coordinates[layer][2][1].getColors());
        coordinates[layer][2][1].setColors(temp);
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                coordinates[layer][i][j].turnUp();
            }
        }
    }
    else if (order == "F'" || order == "B" || order == "MD")
    {
        if (order == "B")
        {
            layer = 2;
        }
        else if (order == "MD")
        {
            layer = 1;
        }
        else
        {
            layer = 0;
        }
        std::vector<char> temp = coordinates[layer][0][0].getColors();
        coordinates[layer][0][0].setColors(coordinates[layer][2][0].getColors());
        coordinates[layer][2][0].setColors(coordinates[layer][2][2].getColors());
        coordinates[layer][2][2].setColors(coordinates[layer][0][2].getColors());
        coordinates[layer][0][2].setColors(temp);
        temp = coordinates[layer][1][0].getColors();
        coordinates[layer][1][0].setColors(coordinates[layer][2][1].getColors());
        coordinates[layer][2][1].setColors(coordinates[layer][1][2].getColors());
        coordinates[layer][1][2].setColors(coordinates[layer][0][1].getColors());
        coordinates[layer][0][1].setColors(temp);
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                coordinates[layer][i][j].turnDown();
            }
        }
    }
    else if (order == "Left")
    {
        rotateCube("U");
        rotateCube("D'");
        rotateCube("ML");
    }
    else if (order == "Right")
    {
        rotateCube("U'");
        rotateCube("D");
        rotateCube("MR");
    }
    else if (order == "Up")
    {
        rotateCube("F");
        rotateCube("B'");
        rotateCube("MU");
    }
    else if (order == "Down")
    {
        rotateCube("F'");
        rotateCube("B");
        rotateCube("MD");
    }
    else if (order == "Clockwise")
    {
        rotateCube("R'");
        rotateCube("L");
        rotateCube("MC");
    }
    else if (order == "AntiClockwise")
    {
        rotateCube("R");
        rotateCube("L'");
        rotateCube("MAC");
    }
    else if (order == "PP")
    {
        rotateCube("R");
        rotateCube("U");
        rotateCube("R'");
        rotateCube("U'");
    }
    else if (order == "PP'")
    {
        rotateCube("L'");
        rotateCube("U'");
        rotateCube("L");
        rotateCube("U");
    }
    else
    {
        std::cout << order << " is an unknown command, try again!\n";
        return 1;
    }
    return 0;
}

void RubiksCube::printPosToFile(std::string nameOfFile)
{
    std::string directory = "D:/ITMO/2 semester/ProgrammingC++/cpplab6/";
    std::string path  = directory + nameOfFile;
    std::ofstream fout(path);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fout << i + 1 << ", " << j + 1 << ", " << k + 1 << " ";
                for (char color : coordinates[i][j][k].getColors())
                {
                    fout << color << " ";
                }
                fout << "\n";
            }
        }
    }
    fout.close();
}

void RubiksCube::getPosFromFile(std::string nameOfFile)
{
    std::string directory = "D:/ITMO/2 semester/ProgrammingC++/cpplab6/";
    std::string path  = directory + nameOfFile;
    std::ifstream fin(path);
    std::vector<char> currentColors(6);
    for (std::string line; getline(fin, line);)
    {
        currentColors[0] = line[8];
        currentColors[1] = line[10];
        currentColors[2] = line[12];
        currentColors[3] = line[14];
        currentColors[4] = line[16];
        currentColors[5] = line[18];
        int c1 = line[0] - '0';
        int c2 = line[3] - '0';
        int c3 = line[6] - '0';
        c1--;
        c2--;
        c3--;
        coordinates[c1][c2][c3].setColors(currentColors);
    }
    fin.close();
}

void RubiksCube::random()
{
    std::vector<std::string> listOfRandom = {"U", "U'", "F", "F'", "R", "R'",
    "B", "B'", "D", "D'", "L", "L'", "Left", "Right", "Clockwise", "AntiClockwise", "Up", "Down"};
    std::srand(std::time(nullptr));
    int rndCycle = 50 + std::rand() % 50;
    for (int i = 0; i < rndCycle; i++)
    {
        int rndAction = std::rand() % 18;
        randomActions.push_back(listOfRandom[rndAction]);
    }
    std::cout << "Finished calculating random position... Showing it in progress:\n";
}

int RubiksCube::yellowOnTop()
{
    int actions = 0;
    if (coordinates[1][2][1]["top"] != 'y')
    {
        if (coordinates[0][1][1]["left"] == 'y')
        {
            solveActions.push_back("AntiClockwise");
            rotateCube("AntiClockwise");
            actions++;
        }
        else if (coordinates[2][1][1]["right"] == 'y')
        {
            solveActions.push_back("Clockwise");
            rotateCube("Clockwise");
            actions++;
        }
        else if (coordinates[1][1][0]["back"] == 'y')
        {
            solveActions.push_back("Up");
            rotateCube("Up");
            actions++;
        }
        else if (coordinates[1][1][2]["front"] == 'y')
        {
            solveActions.push_back("Down");
            rotateCube("Down");
            actions++;
        }
        else if (coordinates[1][0][1]["bot"] == 'y')
        {
            solveActions.push_back("Up");
            solveActions.push_back("Up");
            rotateCube("Up");
            rotateCube("Up");
            actions += 2;
        }
        else
        {
            return 1000;
        }
    }
    return actions;
}
int RubiksCube::whiteFlower()
{
    // take all whites from mid layer
    int actions = 0, errorHandler = 0;
    while (coordinates[1][2][0]["top"] != 'w' || coordinates[0][2][1]["top"] != 'w' ||
           coordinates[2][2][1]["top"] != 'w' || coordinates[1][2][2]["top"] != 'w')
    {
        errorHandler++;
        if (errorHandler > 100)
        {
            return 1000;
        }
        while (coordinates[0][1][0]["back"] == 'w' || coordinates[0][1][0]["left"] == 'w' ||
               coordinates[0][1][2]["front"] == 'w' || coordinates[0][1][2]["left"] == 'w' ||
               coordinates[2][1][0]["back"] == 'w' || coordinates[2][1][0]["right"] == 'w' ||
               coordinates[2][1][2]["front"] == 'w' || coordinates[2][1][2]["right"] == 'w')
        {
            if (coordinates[0][1][2]["left"] == 'w')
            {
                while (coordinates[1][2][2]["top"] == 'w')
                {
                    solveActions.push_back("U");
                    rotateCube("U");
                    actions++;
                }
                solveActions.push_back("R");
                rotateCube("R");
                actions++;
            }
            if (coordinates[0][1][2]["front"] == 'w')
            {
                while (coordinates[0][2][1]["top"] == 'w')
                {
                    solveActions.push_back("U");
                    rotateCube("U");
                    actions++;
                }
                solveActions.push_back("F'");
                rotateCube("F'");
                actions++;
            }
            solveActions.push_back("D'");
            rotateCube("D'");
            solveActions.push_back("ML");
            rotateCube("ML");
            actions += 2;
        }
        //take mid-whites from bot layer
        if ((coordinates[1][2][2]["top"] != 'w' || coordinates[2][2][1]["top"] != 'w' ||
           coordinates[1][2][0]["top"] != 'w' || coordinates[0][2][1]["top"] != 'w'))
        {
            while (coordinates[0][0][1]["left"] == 'w' || coordinates[1][0][0]["back"] == 'w' ||
                   coordinates[2][0][1]["right"] == 'w' || coordinates[1][0][2]["front"] == 'w')
            {
                if (coordinates[0][0][1]["left"] == 'w')
                {
                    while (coordinates[0][2][1]["top"] == 'w')
                    {
                        solveActions.push_back("U");
                        rotateCube("U");
                        actions++;
                    }
                    solveActions.push_back("F");
                    rotateCube("F");
                    solveActions.push_back("U");
                    rotateCube("U");
                    solveActions.push_back("L'");
                    rotateCube("L'");
                    actions += 3;

                }
                solveActions.push_back("D'");
                rotateCube("D'");
                actions++;
            }
            // take mid-whites from top layer
            for (int i = 0; i < 4; i++)
            {
                if (coordinates[0][2][1]["top"] != 'w' && coordinates[0][2][1]["left"] == 'w')
                {
                    solveActions.push_back("F");
                    rotateCube("F");
                    solveActions.push_back("U");
                    rotateCube("U");
                    solveActions.push_back("R");
                    rotateCube("R");
                    actions += 3;
                }
                solveActions.push_back("Left");
                rotateCube("Left");
                actions++;
            }
            // take white from bottom of cube
            for (int i = 0; i < 4; i++)
            {
                if  (coordinates[0][0][1]["bot"] == 'w')
                {
                    while (coordinates[0][2][1]["top"] == 'w')
                    {
                        solveActions.push_back("U");
                        rotateCube("U");
                        actions++;
                    }
                    solveActions.push_back("F");
                    rotateCube("F");
                    solveActions.push_back("F");
                    rotateCube("F");
                    actions += 2;
                }
                solveActions.push_back("D");
                rotateCube("D");
                actions++;
            }
        }
    }
    return actions;
}

int RubiksCube::whiteCross()
{
    int actions = 0, errorHandler = 0;
    for (int i = 0; i < 4; i++)
    {
        while (coordinates[0][2][1]["top"] != 'w' || coordinates[0][2][1]["left"] != coordinates[0][1][1]["left"])
        {
            errorHandler++;
            if (errorHandler > 100)
            {
                return 1000;
            }
            solveActions.push_back("U");
            rotateCube("U");
            actions++;
        }
        solveActions.push_back("F");
        rotateCube("F");
        solveActions.push_back("F");
        rotateCube("F");
        solveActions.push_back("Left");
        rotateCube("Left");
        actions += 3;
    }
    return actions;
}

int RubiksCube::whiteSide()
{
    int actions = 0, errorHandler1 = 0, errorHandler2 = 0;
    while (coordinates[0][0][0]["bot"] != 'w' || coordinates[0][0][1]["bot"] != 'w' || coordinates[0][0][2]["bot"] != 'w' ||
           coordinates[1][0][0]["bot"] != 'w' || coordinates[1][0][1]["bot"] != 'w' || coordinates[1][0][2]["bot"] != 'w' ||
           coordinates[2][0][0]["bot"] != 'w' || coordinates[2][0][1]["bot"] != 'w' || coordinates[2][0][2]["bot"] != 'w')
    {
        errorHandler1++;
        if (errorHandler1 > 300)
        {
            return 1000;
        }
        // check upper layer
        while (coordinates[0][2][0].checkColor('w') || coordinates[0][2][2].checkColor('w') ||
               coordinates[2][2][0].checkColor('w') || coordinates[2][2][2].checkColor('w'))
        {
            errorHandler2++;
            if (errorHandler2 > 300)
            {
                return 1000;
            }
            while (!coordinates[0][2][2].checkColor('w'))
            {
                solveActions.push_back("U'");
                rotateCube("U'");
                actions++;
            }
            if (coordinates[0][2][2]["front"] == 'w')
            {
                while (coordinates[0][2][2]["top"] != coordinates[1][1][2]["front"] || coordinates[0][2][2]["left"] != coordinates[0][1][1]["left"])
                {
                    solveActions.push_back("D'");
                    rotateCube("D'");
                    solveActions.push_back("ML");
                    rotateCube("ML");
                    actions += 2;
                }
                solveActions.push_back("PP");
                rotateCube("PP");
                actions += 4;
            }
            else if (coordinates[0][2][2]["top"] == 'w')
            {
                while (coordinates[0][2][2]["left"] != coordinates[1][1][2]["front"] || coordinates[0][2][2]["front"] != coordinates[0][1][1]["left"])
                {
                    solveActions.push_back("D'");
                    rotateCube("D'");
                    solveActions.push_back("ML");
                    rotateCube("ML");
                    actions += 2;
                }
                for (int j = 0; j < 3; j++)
                {
                    solveActions.push_back("PP");
                    rotateCube("PP");
                    actions += 4;
                }
            }
            else if (coordinates[0][2][2]["left"] == 'w')
            {
                while (coordinates[0][2][2]["front"] != coordinates[1][1][2]["front"] || coordinates[0][2][2]["top"] != coordinates[0][1][1]["left"])
                {
                    solveActions.push_back("D'");
                    rotateCube("D'");
                    solveActions.push_back("ML");
                    rotateCube("ML");
                    actions += 2;
                }
                for (int j = 0; j < 5; j++)
                {
                    solveActions.push_back("PP");
                    rotateCube("PP");
                    actions += 4;
                }
            }
        }
        // check lower layer
        while (coordinates[0][0][0]["back"] == 'w' || coordinates[0][0][0]["left"] == 'w' ||
                coordinates[0][0][2]["front"] == 'w' || coordinates[0][0][2]["left"] == 'w' ||
                coordinates[2][0][0]["back"] == 'w' || coordinates[2][0][0]["right"] == 'w' ||
                coordinates[2][0][2]["front"] == 'w' || coordinates[2][0][2]["right"] == 'w')
        {
            errorHandler1++;
            if (errorHandler1 > 300)
            {
                return 1000;
            }
            while (coordinates[0][0][2]["front"] != 'w' && coordinates[0][0][2]["left"] != 'w')
            {
                solveActions.push_back("D'");
                rotateCube("D'");
                solveActions.push_back("ML");
                rotateCube("ML");
                actions += 2;
            }
            solveActions.push_back("PP");
            rotateCube("PP");
            actions += 4;
        }
    }
    return actions;
}

int RubiksCube::middleLayer()
{
    int actions = 0, midCNT = 0, topCNT = 0;
    for (int i = 0; i < 2; i++)
    {
        // moving corners from mid layer to top
        while ((!coordinates[0][1][0].checkColor('y') && !(coordinates[0][1][0]["left"] == coordinates[0][1][1]["left"] && coordinates[0][1][0]["back"] == coordinates[1][1][0]["back"])) ||
               (!coordinates[2][1][2].checkColor('y') && !(coordinates[2][1][2]["right"] == coordinates[2][1][1]["right"] && coordinates[2][1][2]["front"] == coordinates[1][1][2]["front"]))||
               (!coordinates[2][1][0].checkColor('y') && !(coordinates[2][1][0]["right"] == coordinates[2][1][1]["right"] && coordinates[2][1][0]["back"] == coordinates[1][1][0]["back"]))||
               (!coordinates[0][1][2].checkColor('y') && !(coordinates[0][1][2]["left"] == coordinates[0][1][1]["left"] && coordinates[0][1][2]["front"] == coordinates[1][1][2]["front"])))
        {
            midCNT++;
            if (midCNT > 200)
            {
                return 1000;
            }
            if (!coordinates[0][1][2].checkColor('y') && !(coordinates[0][1][2]["left"] == coordinates[0][1][1]["left"] && coordinates[0][1][2]["front"] == coordinates[1][1][2]["front"]))
            {
                while (!coordinates[1][2][0].checkColor('y'))
                {
                    solveActions.push_back("U");
                    rotateCube("U");
                    actions++;

                }
                solveActions.push_back("PP");
                rotateCube("PP");
                solveActions.push_back("Left");
                rotateCube("Left");
                solveActions.push_back("PP'");
                rotateCube("PP'");
                actions += 9;
            }
            else
            {
                solveActions.push_back("Left");
                rotateCube("Left");
                actions++;
            }
        }
        // moving from top
        int cntU = 0;
        while (!coordinates[1][2][0].checkColor('y') || !coordinates[0][2][1].checkColor('y') ||
               !coordinates[1][2][2].checkColor('y') || !coordinates[2][2][1].checkColor('y'))
        {
            topCNT++;
            if (topCNT > 200)
            {
                return 1000;
            }

            if (coordinates[0][2][1]["left"] == coordinates[0][1][1]["left"] &&
                    coordinates[0][2][1]["top"] == coordinates[1][1][2]["front"])
            {
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("PP");
                rotateCube("PP");
                solveActions.push_back("Left");
                rotateCube("Left");
                solveActions.push_back("PP'");
                rotateCube("PP'");
                actions += 10;
            }
            else if (coordinates[1][2][2]["front"] == coordinates[1][1][2]["front"] &&
                        coordinates[1][2][2]["top"] == coordinates[0][1][1]["left"])
            {
                solveActions.push_back("U'");
                rotateCube("U'");
                solveActions.push_back("PP'");
                rotateCube("PP'");
                solveActions.push_back("Right");
                rotateCube("Right");
                solveActions.push_back("PP");
                rotateCube("PP");
                actions += 10;
            }
            else if (coordinates[1][1][2]["front"] == coordinates[0][1][1]["left"] &&
                     coordinates[1][1][2]["top"] == coordinates[1][1][2]["front"])
            {
                solveActions.push_back("PP");
                rotateCube("PP");
                solveActions.push_back("Left");
                rotateCube("Left");
                solveActions.push_back("PP'");
                rotateCube("PP'");
                actions += 9;
            }
            else
            {
                if (cntU > 3)
                {
                    cntU = 0;
                    solveActions.push_back("Left");
                    rotateCube("Left");
                    actions++;
                }
                else
                {
                    cntU++;
                    solveActions.push_back("U");
                    rotateCube("U");
                    actions++;
                }
            }
        }
    }
    return actions;
}

int RubiksCube::yellowCross()
{
    int actions = 0, yellowCNT = 0;
    while (coordinates[0][2][1]["top"] != 'y' || coordinates[1][2][0]["top"] != 'y' ||
           coordinates[2][2][1]["top"] != 'y' || coordinates[1][2][2]["top"] != 'y' ||
           coordinates[1][2][1]["top"] != 'y')
    {
        yellowCNT++;
        if (yellowCNT > 50)
        {
            return 1000;
        }
        for (int i = 0; i < 4; i++)
        {
            if (coordinates[1][2][0]["top"] == 'y' && coordinates[1][2][1]["top"] == 'y' && coordinates[2][2][1]["top"] == 'y')
            {
                solveActions.push_back("F");
                rotateCube("F");
                solveActions.push_back("PP");
                rotateCube("PP");
                solveActions.push_back("F'");
                rotateCube("F'");
                actions += 6;
                break;
            }
            else
            {
                solveActions.push_back("U");
                rotateCube("U");
                actions++;
            }
        }
        if ((coordinates[1][2][0]["top"] == 'y' && coordinates[1][2][1]["top"] == 'y' && coordinates[1][2][2]["top"] == 'y')
            || (coordinates[2][2][1]["top"] == 'y' && coordinates[1][2][1]["top"] == 'y' && coordinates[0][2][1]["top"] == 'y'))
        {
            if (coordinates[2][2][1]["top"] == 'y' && coordinates[1][2][1]["top"] == 'y' && coordinates[0][2][1]["top"] == 'y')
            {
                solveActions.push_back("U");
                rotateCube("U");
                actions++;
            }
            solveActions.push_back("F");
            rotateCube("F");
            solveActions.push_back("PP");
            rotateCube("PP");
            solveActions.push_back("F'");
            rotateCube("F'");
            actions += 6;
            break;
        }
        else
        {
            solveActions.push_back("F");
            rotateCube("F");
            solveActions.push_back("PP");
            rotateCube("PP");
            solveActions.push_back("F'");
            rotateCube("F'");
            actions += 6;
        }
    }
    return actions;
}


int RubiksCube::completeYellowCross()
{
    int actions = 0, deathHandler = 0;
    bool didSTH = false;
    while (coordinates[0][2][1]["left"] != coordinates[0][1][1]["left"] || coordinates[1][2][2]["front"] != coordinates[1][1][2]["front"] ||
            coordinates[1][2][0]["back"] != coordinates[1][1][0]["back"] || coordinates[2][2][1]["right"] != coordinates[2][1][1]["right"])
    {
        deathHandler++;
        if (deathHandler > 50)
        {
            return 1000;
        }
        for (int i = 0; i < 4; i++)
        {
            if (coordinates[2][2][1]["right"] == coordinates[2][1][1]["right"] && coordinates[1][2][2]["front"] == coordinates[1][1][2]["front"])
            {
                solveActions.push_back("R");
                rotateCube("R");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R'");
                rotateCube("R'");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R");
                rotateCube("R");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R'");
                rotateCube("R'");
                solveActions.push_back("U");
                rotateCube("U");
                didSTH = true;
                actions += 9;
                break;
            }
            else if (coordinates[0][2][1]["left"] == coordinates[0][1][1]["left"] && coordinates[2][2][1]["right"] == coordinates[2][1][1]["right"])
            {
                solveActions.push_back("R");
                rotateCube("R");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R'");
                rotateCube("R'");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R");
                rotateCube("R");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R'");
                rotateCube("R'");
                didSTH = true;
                actions += 8;
                break;
            }
            else
            {
                solveActions.push_back("Left");
                rotateCube("Left");
                actions++;
            }
        }
        if (!didSTH)
        {
            solveActions.push_back("U");
            rotateCube("U");
            actions++;
        }
        else
        {
            didSTH = false;
        }
    }
    return actions;
}

int RubiksCube::topCorners()
{
    int actions = 0, topcornerCNT = 0;
    bool hasCorrectCorner = false;
    while (!coordinates[0][2][0].checkColor(coordinates[0][1][1]["left"]) || !coordinates[0][2][0].checkColor(coordinates[1][1][0]["back"]) ||
           !coordinates[2][2][0].checkColor(coordinates[2][1][1]["right"]) || !coordinates[2][2][0].checkColor(coordinates[1][1][0]["back"]) ||
           !coordinates[0][2][2].checkColor(coordinates[0][1][1]["left"]) || !coordinates[0][2][2].checkColor(coordinates[1][1][2]["front"]) ||
           !coordinates[2][2][2].checkColor(coordinates[2][1][1]["right"]) || !coordinates[2][2][2].checkColor(coordinates[1][1][2]["front"]))
    {
        topcornerCNT++;
        if (topcornerCNT > 50)
        {
            return 1000;
        }

        for (int i = 0; i < 4; i++)
        {
            if (coordinates[0][2][0].checkColor(coordinates[0][1][1]["left"]) && coordinates[0][2][0].checkColor(coordinates[1][1][0]["back"]))
            {
                hasCorrectCorner = true;
                solveActions.push_back("R");
                rotateCube("R");
                solveActions.push_back("U'");
                rotateCube("U'");
                solveActions.push_back("L'");
                rotateCube("L'");
                solveActions.push_back("U");
                rotateCube("U");
                solveActions.push_back("R'");
                rotateCube("R'");
                solveActions.push_back("U'");
                rotateCube("U'");
                solveActions.push_back("L");
                rotateCube("L");
                solveActions.push_back("U");
                rotateCube("U");
                actions += 8;
                break;
            }
            solveActions.push_back("Left");
            rotateCube("Left");
            actions++;

        }
        if (!hasCorrectCorner)
        {
            solveActions.push_back("R");
            rotateCube("R");
            solveActions.push_back("U'");
            rotateCube("U'");
            solveActions.push_back("L'");
            rotateCube("L'");
            solveActions.push_back("U");
            rotateCube("U");
            solveActions.push_back("R'");
            rotateCube("R'");
            solveActions.push_back("U'");
            rotateCube("U'");
            solveActions.push_back("L");
            rotateCube("L");
            solveActions.push_back("U");
            rotateCube("U");
            actions += 8;
        }
    }
    return actions;
}

int RubiksCube::finalStraight()
{
    int actions = 0, finalCNT = 0;
    solveActions.push_back("Up");
    rotateCube("Up");
    solveActions.push_back("Up");
    rotateCube("Up");
    actions += 2;
    for (int i = 0; i < 4; i++)
    {
        while (coordinates[0][0][2]["left"] != coordinates[0][0][1]["left"] || coordinates[0][0][2]["front"] != coordinates[1][0][2]["front"])
        {
            finalCNT++;
            if (finalCNT > 100)
            {
                return 1000;
            }
            solveActions.push_back("PP");
            rotateCube("PP");
            actions += 4;
        }
        solveActions.push_back("D");
        rotateCube("D");
        actions++;
    }
    return actions;
}

void RubiksCube::solve()
{
    std::vector<char> centerColors;
    int actions = yellowOnTop() + whiteFlower() + whiteCross() + whiteSide() + middleLayer() +
    yellowCross() + completeYellowCross() + topCorners() + finalStraight();
    centerColors.push_back(coordinates[1][1][0]["back"]);
    centerColors.push_back(coordinates[0][1][1]["left"]);
    centerColors.push_back(coordinates[1][1][2]["front"]);
    centerColors.push_back(coordinates[2][1][1]["right"]);
    centerColors.push_back(coordinates[1][2][1]["top"]);
    centerColors.push_back(coordinates[1][0][1]["bot"]);
    SmallCube check = SmallCube();
    check.setColors(centerColors);
    if (!(check.checkColor('w') && check.checkColor('y') &&
        check.checkColor('b') && check.checkColor('g') &&
        check.checkColor('r') && check.checkColor('o')))
    {
        solveFlag = false;
        solveActions.clear();
        std::cout << "Incorrect position entered!\n";
        return;
    }
    // LEFT && RIGHT
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (coordinates[0][i][j]["left"] != coordinates[0][1][1]["left"] ||
                coordinates[2][i][j]["right"] != coordinates[2][1][1]["right"])
            {
                solveFlag = false;
                solveActions.clear();
                std::cout << "Incorrect position entered!\n";
                return;
            }
        }
    }
    // FRONT && BACK
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (coordinates[i][j][2]["front"] != coordinates[1][1][2]["front"] ||
                coordinates[i][j][0]["back"] != coordinates[1][1][0]["back"])
            {
                solveFlag = false;
                solveActions.clear();
                std::cout << "Incorrect position entered!\n";
                return;
            }
        }
    }
    // TOP && BOT
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (coordinates[i][2][j]["top"] != coordinates[1][2][1]["top"] ||
                coordinates[i][0][j]["bot"] != coordinates[1][0][1]["bot"])
            {
                solveFlag = false;
                solveActions.clear();
                std::cout << "Incorrect position entered!\n";
                return;
            }
        }
    }
    if (actions < 600)
    {
        solveFlag = true;
        std::cout << "Finished calculating solution using " << actions << " steps! Showing it in progress:\n";
    }
    else
    {
        solveFlag = false;
        solveActions.clear();
        std::cout << "Incorrect position entered!\n";
    }
}
