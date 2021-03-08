#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("hamiltonian.in");
ofstream fout("hamiltonian.out");

int checkAnswer(vector<vector<int>>&availableways, vector<int>&answer){
    int node;
    for(int i = answer.size() - 1; i > 0; i--){
        bool wasAnswer = true;
        node = answer[i];
        for(int j = 0; j < availableways[node].size(); j++){
            if(availableways[node][j] == answer[i - 1]){
                wasAnswer = false;
            }
        }
        if(wasAnswer){
            return 0;
         }
    }
    return 1;
}
int dfs(int node, int infoaboutnodes[], vector<vector<int>>&availableways, vector<int>&answer){
    int updnode;
    infoaboutnodes[node] = 1;
    for(int i = 0; i < availableways[node].size(); i++){
        updnode = availableways[node][i];
        if(!infoaboutnodes[updnode]){
            dfs(updnode, infoaboutnodes, availableways, answer);
        }
    }
    answer.push_back(node);
}

int main()
{
    int numOfNodes, lines;
    fin >> numOfNodes >> lines;

    int infoAboutNodes[numOfNodes];
    vector<int> answer;
    vector<vector<int>> availableWays(numOfNodes, vector<int>());

    for(int i = 0; i < numOfNodes; i++){
        infoAboutNodes[i] = 0; // not visited node; 1 - visited
    }

    for(int i = 0; i < lines; i++){
        int startNode, endNode;
        fin >> startNode >> endNode;
        availableWays[startNode - 1].push_back(endNode - 1);
    }

    for(int i = 0; i < numOfNodes; i++){
        if(!infoAboutNodes[i]){
            dfs(i, infoAboutNodes, availableWays, answer);
        }
    }

    if(checkAnswer(availableWays, answer)){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    return 0;
}
