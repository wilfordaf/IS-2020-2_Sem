#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;

const long long INF = 8e18;

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

void dfs(int node, vector<bool>& infoAboutNodesDFS, vector<vector<int>>& availableWaysDFS){
    infoAboutNodesDFS[node] = true;
    for (int i = 0; i < availableWaysDFS[node].size(); i++)
    {
        int updNode = availableWaysDFS[node][i];
        if (!infoAboutNodesDFS[updNode])
        {
            dfs(updNode, infoAboutNodesDFS, availableWaysDFS);
        }
    }
}

void fordBellman(int s, int numOfNodes, vector<long long>& d, vector<int>& prev, vector<Edge>& Edges,
                              vector<bool>& infoAboutNodes, vector<vector<int>>& availableWays)
{
    d[s] = 0;
    int v;
    for (int i = 0; i < numOfNodes; i++)
    {
        v = -1;
        for (Edge e : Edges)
        {
            if (d[e.startNode] < INF)
            {
                if (d[e.endNode] > d[e.startNode] + e.length)
                {
                    d[e.endNode] = max(-INF, d[e.startNode] + e.length);
                    prev[e.endNode] = e.startNode;
                    v = e.endNode;
                }
            }
        }
    }

    if (v != -1)
    {
        for (int i = 0; i < numOfNodes; i++)
        {
            v = prev[v];
        }

        dfs(v, infoAboutNodes, availableWays);

        for (int i = 0; i < numOfNodes; i++)
        {
            if (infoAboutNodes[i])
            {
               d[i] = -INF;
            }
        }
    }
}

int main()
{
    ifstream fin("path.in");
    ofstream fout("path.out");

    int numOfNodes, numOfEdges, highlightedNode;
    fin >> numOfNodes >> numOfEdges >> highlightedNode;

    vector<Edge> Edges;
    vector<long long> d(numOfNodes, INF);
    vector<int> prev(numOfNodes, -1);
    vector<vector<int>> availableWays(numOfNodes, vector<int>());
    vector<bool> infoAboutNodes(numOfNodes, false);

    for (int i = 0; i < numOfEdges; i++)
    {
        int v1, v2;
        long long w;
        fin >> v1 >> v2 >> w;
        Edges.push_back(Edge(v1-1, v2-1, w));
        availableWays[v1-1].push_back(v2-1);
    }

    fordBellman(highlightedNode - 1, numOfNodes, d, prev, Edges, infoAboutNodes, availableWays);

    for (auto answer : d)
    {
        if (answer == INF)
        {
            fout << "*" << "\n";
        }
        else if (answer == -INF)
        {
            fout << "-" << "\n";
        }
        else
        {
            fout << answer << "\n";
        }
    }
    return 0;
}
