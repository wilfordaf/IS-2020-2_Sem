#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
const int INF = (int) 1e6;
int main()
{
    ifstream fin("knapsack.in");
    ofstream fout("knapsack.out");
    int S, N, max1 = 0;
    fin >> S >> N;
    vector<int> weights(INF, INF);
    weights[0] = 1;
    for (int i = 0; i < N; i++)
    {
        int w;
        fin >> w;
        for (int j = S; j >= w; j--)
        {
            if (weights[j - w] == 1)
            {
                weights[j] = 1;
                if (j > max1)
                {
                    max1 = j;
                }
            }
        }
    }
    fout << max1;
    return 0;