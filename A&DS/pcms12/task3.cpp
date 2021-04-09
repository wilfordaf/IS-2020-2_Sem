#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

void LCS(int lenX, int lenY, string str1, string str2, vector<int>& lastMatrixStr)
{
    vector<vector<int>> k(2, vector<int>(lenY + 1));
    {
        for (int j = 0; j <= lenY; j++)
        {
            k[1][j] = 0;
        }
        for (int i = 0; i < lenX; i++)
        {
            for (int j = 0; j <= lenY; j++)
            {
                k[0][j] = k[1][j];
            }

            for (int j = 1; j <= lenY; j++)
            {
                if (str1[i] == str2[j - 1])
                {
                    k[1][j] = k[0][j - 1] + 1;
                }
                else
                {
                    k[1][j] = max(k[1][j - 1], k[0][j]);
                }
            }

        }
    }
    for (int j = 0; j <= lenY; j++)
    {
        lastMatrixStr[j] = k[1][j];
    }
}

void Hirschberg(int lenX, int lenY, string str1, string str2)
{
    if (lenY == 0)
    {
        return;
    }

    if (lenX == 1)
    {
        int f = str2.find_first_of(str1[0]);
        if (f != string::npos)
        {
            cout << str1[0];
        }
        return;
    }

    vector<int> l1(lenY + 1);
    vector<int> l2(lenY + 1);
    int mid = lenX / 2;

    LCS(mid, lenY, str1.substr(0, mid), str2, l1);

    string str1_second = str1;
    string str2_second = str2;
    reverse(str1_second.begin(), str1_second.end());
    reverse(str2_second.begin(), str2_second.end());

    LCS(mid + 1, lenY, str1_second.substr(0, lenX - mid), str2_second, l2);

    int maxV = l2[0], maxJ = 0;

    for (int j = 0; j <= lenY; j++)
    {
        if (l1[j] + l2[lenY - j] > maxV)
        {
            maxV = l1[j] + l2[lenY - j];
            maxJ = j;
        }
    }

    if (!mid)
    {
        mid++;
    }
    if (l1[lenY] > maxV)
    {
        maxJ = lenY;
    }

    Hirschberg(mid, maxJ, str1.substr(0, mid), str2.substr(0, maxJ));
    Hirschberg(lenX - mid, lenY - maxJ, str1.substr(mid, lenX), str2.substr(maxJ, lenY));
}
int main()
{
    string str1, str2;
    cin >> str1 >> str2;
    Hirschberg(str1.length(), str2.length(), str1, str2);
    return 0;
}
