#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void dfs(int node, int group, int infoaboutnodes[][2], vector<vector<int>>&availableways){
    int updnode;
    infoaboutnodes[node][0] = 1;
    infoaboutnodes[node][1] = group;
    for(int i = 0; i < availableways[node].size(); i++){
        updnode = availableways[node][i];
        if(infoaboutnodes[updnode][0] == 0){
            dfs(updnode, group, infoaboutnodes, availableways);
        }
    }
}

int main()
{
    ifstream fin("components.in");
    ofstream fout("components.out");

    int n, m, temp, cnt = 1;

    fin >> n >> m;

    int infoaboutnodes[n][2];
    vector<vector<int>> availableways(n, vector<int>());

    for(int i = 0; i < n; i++){
        infoaboutnodes[i][0] = 0;
        infoaboutnodes[i][1] = -1;
    }

    for(int i = 0; i < m; i++){
        int x, y;
        fin >> x >> y;
        availableways[x - 1].push_back(y - 1);
        availableways[y - 1].push_back(x - 1);
    }

    for(int i = 0; i < n; i++){
        if(infoaboutnodes[i][0] == 0){
            dfs(i, cnt, infoaboutnodes, availableways);
            cnt++;

        }
    }
    fout << cnt - 1 << endl;

    for(int i = 0; i < n; i++){
        fout << infoaboutnodes[i][1] << " ";
    }

    return 0;
}
