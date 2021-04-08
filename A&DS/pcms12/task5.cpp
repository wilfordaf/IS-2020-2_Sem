#include <iostream>
#include <vector>
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
    int numOfNodes, root;
    cin >> numOfNodes;
    vector<pair<int, int>> d(numOfNodes, make_pair(0 , 1));
    vector<vector<int>> availableWays(numOfNodes, vector<int>());

    for (int i = 0; i < numOfNodes; i++)
    {
        int node;
        cin >> node;
        if (node != 0)
        {
            node--;
            availableWays[node].push_back(i);
        }
        else
        {
            root = i;
        }
    }

    dfs(root, availableWays, d);

    cout << max(d[root].first, d[root].second);
    return 0;
}
