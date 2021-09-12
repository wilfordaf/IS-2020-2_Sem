#include <iostream>
#include <GL/glut.h>
#include <string>
#include "rubikscube.h"
#define WinWidth 640
#define WinHeight 480

float xrot = 0.0f;
float yrot = 0.0f;
std::string buffer = "";
std::vector<std::string> solveActions;
std::vector<std::string> randomActions;
bool solveFlag = false;
int timer = 0;
int timerLimit = 50;
RubiksCube rc = RubiksCube();
RubiksCube invisible = RubiksCube();


void initGL() {
   glClearColor(0.658824, 0.658824, 0.658824, 1);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void execute()
{
    std::cout << buffer << "\n";
    if (buffer == "X")
    {
        xrot += 90.0f;
    }
    else if(buffer == "Y")
    {
        yrot += 90.0f;
    }
    else if (buffer == "!r")
    {
        rc.random();
    }
    else if (buffer == "!s")
    {
        invisible.solve();
    }
    else if (buffer.substr(0, 2) == "!p")
    {
        std::string nameOfFile = buffer.substr(3, buffer.length());
        rc.printPosToFile(nameOfFile);
        std::cout << "Position was copied to file " << nameOfFile << "!\n";
    }
    else if (buffer.substr(0, 2) == "!g")
    {
        std::string nameOfFile = buffer.substr(3, buffer.length());
        rc.getPosFromFile(nameOfFile);
        invisible.getPosFromFile(nameOfFile);
        std::cout << "Position was copied from file " << nameOfFile << "!\n";
    }
    else if (buffer == "+")
    {
        timerLimit -= 10;
    }
    else if (buffer == "-")
    {
        timerLimit += 10;
    }
    else
    {
        if(!rc.rotateCube(buffer))
        {
            invisible.rotateCube(buffer);
        }
    }
}

void keyboard(unsigned char key, int, int)
{
    switch(key)
    {
    case 13:
        execute();
        buffer = "";
        break;
    default:
        buffer += key;
        break;
    }
    glutPostRedisplay();
}


void display()
{
    if (!randomActions.empty())
    {
        if (timer > timerLimit)
        {
            timer = 0;
            std::string action = randomActions.front();
            randomActions.erase(randomActions.begin());
            rc.rotateCube(action);
            invisible.rotateCube(action);
        }
    }
    if (solveFlag)
    {
        if (!solveActions.empty() && randomActions.empty())
        {
            if (timer > timerLimit)
            {
                timer = 0;
                std::string action = solveActions.front();
                solveActions.erase(solveActions.begin());
                std::cout << action << "\n";
                rc.rotateCube(action);
            }
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -9.0f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    rc.drawRubiksCube();
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)
    {
        height = 1;
    }
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
}

void timer_all(int)
{
    timer++;
    glutPostRedisplay();
    glutTimerFunc(15, timer_all, 0);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WinWidth, WinHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Rubik`s Cube");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer_all, 0);
    initGL();
    glutMainLoop();
    return 0;
}
