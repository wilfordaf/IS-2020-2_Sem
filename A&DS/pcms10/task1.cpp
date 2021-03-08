#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");


int main()
{
    int numOfNodes, lines;
    fin >> numOfNodes >> lines;

    vector<vector<int>> availableWays(numOfNodes, vector<int>());


    for(int i = 0; i < lines; i++){
        int startNode, endNode;
        fin >> startNode >> endNode;
        availableWays[startNode - 1].push_back(endNode - 1);
        availableWays[endNode - 1].push_back(startNode - 1);
    }

    for(int i = 0; i < numOfNodes; ++i){
        fout << availableWays[i].size() << " ";
    }

    return 0;
}
