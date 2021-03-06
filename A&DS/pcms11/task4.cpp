#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

const long long INF = (long long) 8e18;

class Edge
{
public:
    int startNode;
    int endNode;
    long long length;
    Edge(int startNode_, int endNode_, long long length_)
    {
        startNode = startNode_;
        endNode = endNode_;
        length = length_;
    }
};

void dfs(int node, vector<bool>& infoAboutNodes, vector<vector<int>>& availableWays, vector<long long>& d){
    infoAboutNodes[node] = true;
    d[node] = -INF;
    for (auto newNode : availableWays[node])
    {
        if (!infoAboutNodes[newNode])
        {
            dfs(newNode, infoAboutNodes, availableWays, d);
        }
    }
}

void fordBellman(int s, int numOfNodes, vector<long long>& d, vector<int>& prev, vector<Edge>& Edges, vector<bool>& infoAboutNodes, vector<vector<int>>& availableWays)
{
    d[s] = 0;
    set<int> strangeNodes;
    for (int i = 0; i < numOfNodes; i++)
    {
        for (Edge e : Edges)
        {
            if (d[e.startNode] < INF)
            {
                if (d[e.endNode] > d[e.startNode] + e.length)
                {
                    d[e.endNode] = max(-INF, d[e.startNode] + e.length);
                    prev[e.endNode] = e.startNode;
                }
            }
        }

    }

    for (Edge e : Edges)
    {
        if (d[e.startNode] < INF)
        {
            if (d[e.endNode] > d[e.startNode] + e.length)
            {
                strangeNodes.insert(e.endNode);
            }
        }
    }

    for (auto vert : strangeNodes)
    {
        for (int i = 0; i < numOfNodes; i++)
        {
            vert = prev[vert];
        }
        dfs(vert, infoAboutNodes, availableWays, d);
    }
}

int main()
{
    ifstream fin("path.in");
    ofstream fout("path.out");

    int numOfNodes, numOfEdges, highlightedNode;
    fin >> numOfNodes >> numOfEdges >> highlightedNode;


    vector<Edge> Edges;
    vector<int> prev(numOfNodes, -1);
    vector<vector<int>> availableWays(numOfNodes);
    vector<bool> infoAboutNodes(numOfNodes, false);
    vector<long long> d(numOfNodes, INF);

    for (int i = 0; i < numOfEdges; i++)
    {
        int v1, v2;
        long long w;
        fin >> v1 >> v2 >> w;
        Edges.emplace_back(Edge(v1 - 1, v2 - 1, w));
        availableWays[v1 - 1].push_back(v2 - 1);
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
