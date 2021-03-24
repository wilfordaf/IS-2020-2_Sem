#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

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

// dfs for verification if we can reach any node from this
void dsf(int node, vector<bool>& infoAboutNodesDFS, vector<vector<int>>& availableWaysDFS){
    int updNode;
    infoAboutNodesDFS[node] = true;
    for (int i = 0; i < availableWaysDFS[node].size(); i++)
    {
        updNode = availableWaysDFS[node][i];
        if (!infoAboutNodesDFS[updNode])
        {
            dsf(updNode, infoAboutNodesDFS, availableWaysDFS);
        }
    }
}

// dfs for condesation
void dfs(int node, vector<bool>& infoAboutNodesDFS, vector<vector<int>>& availableWaysDFS, vector<int>& part, int curPart){
    infoAboutNodesDFS[node] = true;
    part[node] = curPart;
    for (int i = 0; i < availableWaysDFS[node].size(); i++)
    {
        int updNode = availableWaysDFS[node][i];
        if (!infoAboutNodesDFS[updNode])
        {
            dfs(updNode, infoAboutNodesDFS, availableWaysDFS, part, curPart);
        }
    }
}

//inverted dfs for condensation
void opDFS(int node, vector<bool>& infoAboutNodesOPDFS, vector<vector<int>>&availableWaysOPDFS, vector<int>& exit){
    infoAboutNodesOPDFS[node] = true;
    for (int i = 0; i < availableWaysOPDFS[node].size(); i++)
    {
        int updnode = availableWaysOPDFS[node][i];
        if (!infoAboutNodesOPDFS[updnode])
        {
            opDFS(updnode, infoAboutNodesOPDFS, availableWaysOPDFS, exit);
        }
    }
    exit.push_back(node);
}

//condensation, which returns amount of components
int condensation(vector<bool>& infoAboutNodesDFS, vector<vector<int>>& availableWaysDFS, vector<bool>& infoAboutNodesOPDFS,
                  vector<vector<int>>&availableWaysOPDFS, vector<int>& exit, vector<int>& part, int numOfNodes)
{
     for (int i = 0; i < numOfNodes; i++)
    {
        if (!infoAboutNodesOPDFS[i])
        {
            opDFS(i, infoAboutNodesOPDFS, availableWaysOPDFS, exit);
        }
    }

    int cnt = 0;

    for (int i = exit.size() - 1; i >= 0; i--)
    {
        if (!infoAboutNodesDFS[exit[i]])
        {
            dfs(exit[i], infoAboutNodesDFS, availableWaysDFS, part, cnt);
            cnt++;
        }
    }
    return cnt;
}

//algorythm of 2 chinese
long long findMST(vector<Edge>& Edges, int numOfNodes, int root)
{
    long long res = 0;

    //find minimal edge to each node
    vector<int> minEdge(numOfNodes, INT_MAX);
    for (auto edge : Edges)
    {
        minEdge[edge.endNode] = min(edge.length, minEdge[edge.endNode]);
    }
    minEdge[root] = 0;
    //add minimals to the result, cause it definitely contains them
    for (int i = 0; i < numOfNodes; i++)
    {
        res += minEdge[i];
    }
    //adding zeroEdges to each node & filling ways from each node for condensation
    vector<Edge> zeroEdges;
    vector<vector<int>> availableWaysDFS(numOfNodes, vector<int>());
    vector<vector<int>> availableWaysOPDFS(numOfNodes, vector<int>());
    vector<bool> infoAboutNodesDFS(numOfNodes, false);
    vector<bool> infoAboutNodesOPDFS(numOfNodes, false);

    for (auto edge : Edges)
    {
        if (edge.length == minEdge[edge.endNode])
        {
            Edge e1 = Edge(edge.startNode, edge.endNode, edge.length - minEdge[edge.endNode]);
            zeroEdges.push_back(e1);
            availableWaysDFS[edge.startNode].push_back(edge.endNode);
            availableWaysOPDFS[edge.endNode].push_back(edge.startNode);
        }

    }
    //if we can reach any node from this, return result, else continue algorythm
    dsf(root, infoAboutNodesDFS, availableWaysDFS);
    bool passedAll = true;
    for (auto statement : infoAboutNodesDFS)
    {
        if (statement)
        {
            statement = false;
        }
        else
        {
            passedAll = false;
        }
    }
    if (passedAll)
    {
        return res;
    }
    //construct connection components to bigger nodes by using condensation

    vector<int> exit;
    vector<int> part(numOfNodes, 0);
    int componentsCount = condensation(infoAboutNodesDFS, availableWaysDFS, infoAboutNodesOPDFS,
                                   availableWaysOPDFS, exit, part, numOfNodes);

    //making new edges between new big nodes
    vector<Edge> newEdges;
    for (auto edge : Edges)
    {
        if (part[edge.startNode] != part[edge.endNode])
        {
            Edge e2 = Edge(part[edge.startNode], part[edge.endNode], edge.length - minEdge[edge.endNode]);
            newEdges.push_back(e2);
        }
    }
    res += findMST(newEdges, componentsCount, part[root]);
    return res;
}

int main()
{
    ifstream fin("chinese.in");
    ofstream fout("chinese.out");

    int numOfNodes, numOfEdges;

    fin >> numOfNodes >> numOfEdges;

    vector<Edge> Edges;
    vector<bool> infoAboutNodesDFS_(numOfNodes, false);
    vector<vector<int>> availableWaysDFS_(numOfNodes, vector<int>());

    for (int i = 0; i < numOfEdges; i++)
    {
        int v1, v2, w;
        fin >> v1 >> v2 >> w;
        Edges.push_back(Edge(v1 - 1, v2 - 1, w));
        availableWaysDFS_[v1 - 1].push_back(v2 - 1);
    }

    dsf(0, infoAboutNodesDFS_, availableWaysDFS_);
    bool passAll = true;
    for (auto statement : infoAboutNodesDFS_)
    {
        if (!statement)
        {
            passAll = false;
            break;
        }
    }

    if (passAll)
    {
        long long answer = findMST(Edges, numOfNodes, 0);
        fout << "YES" << "\n" << answer;
    }
    else
    {
        fout << "NO";
    }
    return 0;
}
