#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int solve(int x, int y, int borderX, int borderY, vector<vector<int>>& field)
{
    if (x < 1 || y < 1 || x > borderX || y > borderY)
    {
        return 0;
    }
    if (x == 1 && y == 1)
    {
        field[x][y] = 1;
        return 1;
    }

    if (field[x][y] != -1)
    {
        return field[x][y];
    }

    field[x][y] = solve(x - 2, y - 1, borderX, borderY, field) + solve(x - 2, y + 1, borderX, borderY, field) +
    solve(x + 1, y - 2, borderX, borderY, field) + solve(x - 1, y - 2, borderX, borderY, field);
    return field[x][y];
}
int main()
{
    ifstream fin("knight2.in");
    ofstream fout("knight2.out");
    int N, M;
    fin >> N >> M;
    vector<vector<int>> field(N + 1, vector<int>(M + 1, -1));

    fout << solve(N, M, N, M, field);
    return 0;
}
