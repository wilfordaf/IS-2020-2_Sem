#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <float.h>

using namespace std;

class Point
{
public:
    int x;
    int y;
    Point(int x_, int y_)
    {
        x = x_;
        y = y_;
    }
};

double lengthOfEdge(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main()
{
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");
    int numOfPoints;

    fin >> numOfPoints;
    vector<Point> Points;
    vector<vector<double>> len(numOfPoints, vector<double>(numOfPoints));
    vector<bool> isUsed(numOfPoints, false);
    vector<double> minDist(numOfPoints, DBL_MAX);
    minDist[0] = 0;
    double answer = 0;


    for (int i = 0; i < numOfPoints; i++)
    {
        int x, y;
        fin >> x >> y;
        Points.push_back(Point(x, y));
    }

    for (int i = 0; i < numOfPoints; i++)
    {
        for (int j = 0; j < numOfPoints; j++)
        {
            if (i == j)
            {
                len[i][j] = DBL_MAX;
            }
            else
            {
                len[i][j] = lengthOfEdge(Points[i], Points[j]);
            }
        }
    }

    for (int i = 0; i < numOfPoints; i++)
    {
        int numOfNewPoint = 0;
        double minimal_distance = DBL_MAX;
        for (int j = 0; j < numOfPoints; j++)
        {
            if (!isUsed[j] && minDist[j] < minimal_distance)
            {
                numOfNewPoint = j;
                minimal_distance = minDist[j];
            }
        }
        isUsed[numOfNewPoint] = true;
        answer += minimal_distance;
        for (int k = 0; k < numOfPoints; k++)
        {
            minDist[k] = min(minDist[k], len[numOfNewPoint][k]);
        }
    }
    fout << setprecision(10) << answer;
    return 0;
}
