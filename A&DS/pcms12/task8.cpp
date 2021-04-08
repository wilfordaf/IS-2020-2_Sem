#include <iostream>
#include <vector>
using namespace std;
const long long divider = 1000000000;

long long palSubSeq(int left, int right, vector<vector<long long>>& palindroms, vector<long long>& a)
{
    if (palindroms[left][right] == -1)
    {
        if (a[left] != a[right])
        {
            palindroms[left][right] = (palSubSeq(left, right - 1, palindroms, a) + palSubSeq(left + 1, right, palindroms, a) - palSubSeq(left + 1, right - 1, palindroms, a) + divider) % divider;
        }
        else
        {
            palindroms[left][right] = (palSubSeq(left, right - 1, palindroms, a) + palSubSeq(left + 1, right, palindroms, a) + 1)  % divider;
        }
    }
    return palindroms[left][right];
}


int main()
{
    int amount;
    cin >> amount;
    vector<vector<long long>> palindroms(amount, vector<long long>(amount));
    vector<long long> a;

    for (int i = 0; i < amount; i++)
    {
        long long ai;
        cin >> ai;
        a.push_back(ai);
    }

    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if (i == j)
            {
                palindroms[i][j] = 1;
            }
            else if (i > j)
            {
                palindroms[i][j] = 0;
            }
            else
            {
                palindroms[i][j] = -1;
            }
        }
    }

    cout << palSubSeq(0, amount - 1, palindroms, a);
    return 0;
}
