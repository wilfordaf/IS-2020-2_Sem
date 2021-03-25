#include <iostream>
#include <vector>
#include <fstream>
#include <limits.h>
using namespace std;

class Edge
{
public:
    int startNode;
    int endNode;
    int length;
    Edge(int startNode_, int endNode_, int length_)
    {
        startNode = startNode_;
        endNode = endNode_;
        length = length_;
    }
};

void fordBellman(int s, vector<long long>& d, vector<Edge>& Edges)
{
    d[s] = 0;
    while (true)
    {
        bool any = false;
        for (auto edge : Edges)
        {
            if (d[edge.startNode] < INT_MAX)
            {
                if (d[edge.endNode] > d[edge.startNode] + edge.length)
                {
                    d[edge.endNode] = d[edge.startNode] + edge.length;
                    any = true;
                }
            }
        }
        if (!any)
        {
          break;
        }
    }
}
int main()
{
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");

    int numOfNodes, numOfEdges;
    fin >> numOfNodes >> numOfEdges;

    vector<Edge> Edges;

    for (int i = 0; i < numOfEdges; i++)
    {
        int v1, v2, len;
        fin >> v1 >> v2 >> len;
        Edges.push_back(Edge(v1 - 1, v2 - 1, len));
    }

    for (int i = 0; i < numOfNodes; i++)
    {
        vector<long long> d(numOfNodes, INT_MAX);
        fordBellman(i, d, Edges);
        for (int j = 0; j < numOfNodes; j++)
        {
            fout << d[j] << " ";
        }
        fout << "\n";
    }
    return 0;
}
