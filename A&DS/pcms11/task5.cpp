#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;

const long long INF = 100000000001;

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

vector<int> negativeCycle(int numOfNodes, vector<long long>& d, vector<int>& prev, vector<Edge>& Edges)
{
    int v;
    vector<int> path;
    for (int i = 0; i < numOfNodes; i++)
    {
        v = -1;
        for (Edge e : Edges)
        {
            if (d[e.endNode] > d[e.startNode] + e.length)
            {
                d[e.endNode] = max(-INF, d[e.startNode] + e.length);
                prev[e.endNode] = e.startNode;
                v = e.endNode;
            }
        }
    }

    if (v != -1)
    {
        int u = v;
        for (int i = 0; i < numOfNodes; i++)
        {
            u = prev[u];
        }
        for (int current = u; ; current = prev[current])
        {
            path.push_back(current);
            if (current == u && path.size() > 1)
            {
                break;
            }
        }
    }
    return path;
}

int main()
{
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");

    int numOfNodes;
    fin >> numOfNodes;

    vector<Edge> Edges;
    vector<long long> d(numOfNodes, INF);
    vector<int> prev(numOfNodes, -1);


    for (int i = 0; i < numOfNodes; i++)
    {
        for (int j = 0; j < numOfNodes; j++)
        {
            long long w;
            fin >> w;
            if (w != 1000000000)
            {
                Edges.push_back(Edge(i, j, w));
            }

        }

    }

    vector<int> cycle = negativeCycle(numOfNodes, d, prev, Edges);
    if (cycle.size())
    {
        fout << "YES" << "\n" << cycle.size() << "\n";
        for (int i = cycle.size() - 1; i >= 0; i--)
        {
            fout << cycle[i] + 1 << " ";
        }
    }
    else
    {
        fout << "NO";
    }

    return 0;
}
