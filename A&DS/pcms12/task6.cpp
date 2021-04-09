#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void dfs(int v, vector<vector<int>>& availableWays, vector<pair<int, int>>& d)
{
    for (auto u : availableWays[v])
    {
        dfs(u, availableWays, d);
    }
    for (auto u : availableWays[v])
    {
        d[v].second += d[u].first;
        d[v].first += max(d[u].first, d[u].second);
    }
}

int main()
{
    ifstream fin("selectw.in");
    ofstream fout("selectw.out");

    int numOfNodes, root;
    fin >> numOfNodes;
    vector<pair<int, int>> d;
    vector<vector<int>> availableWays(numOfNodes);

    for (int i = 0; i < numOfNodes; i++)
    {
        int node, value;
        fin >> node >> value;
        if (node != 0)
        {
            node--;
            availableWays[node].push_back(i);
        }
        else
        {
            root = i;
        }
        d.emplace_back(0, value);
    }

    dfs(root, availableWays, d);

    fout << max(d[root].first, d[root].second);
    return 0;
}
