#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int i, j, x, y, n, m;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fin >> n >> m;
    int matrix[n][n];
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }

    for(i = 0; i < m; i++){
        fin >> x >> y;
        matrix[x-1][y-1] = 1;
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            fout << matrix[i][j] << " ";
        }
        fout << "\n";
    }
    return 0;
}
