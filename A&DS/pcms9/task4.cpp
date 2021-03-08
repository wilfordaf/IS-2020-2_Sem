#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("cond.in");
ofstream fout("cond.out");


void dfs(int node, int infoaboutnodesDFS[], vector<vector<int>>&availablewaysDFS, vector<int>&part, int curPart){
    infoaboutnodesDFS[node] = 1;
    part[node] = curPart;
    for(int i = 0; i < availablewaysDFS[node].size(); i++){
        int updnode = availablewaysDFS[node][i];
        if(!infoaboutnodesDFS[updnode]){
            dfs(updnode, infoaboutnodesDFS, availablewaysDFS, part, curPart);
        }
    }
}

void opDFS(int node, int infoaboutnodesOPDFS[], vector<vector<int>>&availablewaysOPDFS, vector<int>&exit){
    infoaboutnodesOPDFS[node] = 1;
    for(int i = 0; i < availablewaysOPDFS[node].size(); i++){
        int updnode = availablewaysOPDFS[node][i];
        if(!infoaboutnodesOPDFS[updnode]){
            opDFS(updnode, infoaboutnodesOPDFS, availablewaysOPDFS, exit);
        }
    }
    exit.push_back(node);
}

int main()
{
    int numOfNodes, lines;
    fin >> numOfNodes >> lines;

    int infoAboutNodesDFS[numOfNodes];
    int infoAboutNodesOPDFS[numOfNodes];
    vector<int> part(numOfNodes, 0);
    vector<vector<int>> availableWaysDFS(numOfNodes, vector<int>());
    vector<vector<int>> availableWaysOPDFS(numOfNodes, vector<int>());
    vector<int> exit;

    for(int i = 0; i < numOfNodes; i++){
        infoAboutNodesDFS[i] = 0;
        infoAboutNodesOPDFS[i] = 0;
    }

    for(int i = 0; i < lines; i++){
        int startNode, endNode;
        fin >> startNode >> endNode;
        availableWaysDFS[startNode - 1].push_back(endNode - 1);
        availableWaysOPDFS[endNode - 1].push_back(startNode - 1);
    }

    for(int i = 0; i < numOfNodes; i++){
        if(!infoAboutNodesOPDFS[i]){
            opDFS(i, infoAboutNodesOPDFS, availableWaysOPDFS, exit);
        }
    }

    int cnt = 1;
    for(int i = exit.size() - 1; i >= 0; i--){
        if(!infoAboutNodesDFS[exit[i]]){
            dfs(exit[i], infoAboutNodesDFS, availableWaysDFS, part, cnt);
            cnt++;
        }
    }

    fout << cnt - 1 << endl;
    for(int i = 0; i < numOfNodes; i++){
        fout << cnt - part[i] << " ";
    }
    return 0;
}
