#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const long long INF = 100000000001;
void dijkstra(int s, int numOfNodes, vector<long long>& d, vector<bool>& used,
              vector<vector<int>>& availableWays, vector<vector<long long>>& lengthsOfWays)
{
    d[s - 1] = 0;
    for (int i = 0; i < numOfNodes; i++)
    {
        int v = -1;
        for (int j = 0; j < numOfNodes; j++)
        {
            if (!used[j] && (v == -1 || d[j] < d[v]))
            {
                v = j;
            }

        }
        if (d[v] == INF)
        {
            break;
        }
        used[v] = true;
        for (int j = 0; j < availableWays[v].size(); j++)
        {
            if (d[availableWays[v][j]] > d[v] + lengthsOfWays[v][j])
            {
                d[availableWays[v][j]] = d[v] + lengthsOfWays[v][j];
            }
        }
    }
}
int main()
{
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

    int numOfNodes, startNode, endNode;
    fin >> numOfNodes >> startNode >> endNode;

    vector<vector<int>> availableWays(numOfNodes, vector<int>());
    vector<vector<long long>> lengthsOfWays(numOfNodes, vector<long long>());
    vector<long long> d(numOfNodes, INF);
    vector<bool> used(numOfNodes, false);

    for (int i = 0; i < numOfNodes; i++)
    {
        for (int j = 0; j < numOfNodes; j++)
        {
            long long len;
            fin >> len;
            if (i != j && len != -1)
            {
                availableWays[i].push_back(j);
                lengthsOfWays[i].push_back(len);
            }
        }
    }

    dijkstra(startNode, numOfNodes, d, used, availableWays, lengthsOfWays);
    if (d[endNode - 1] != INF)
    {
        fout << d[endNode - 1];
    }
    else
    {
        fout << -1;
    }
    return 0;
}
