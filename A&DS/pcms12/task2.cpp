#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int binSearch(vector<long long>& a, long long key)
{
    int l = -1, r = a.size();
    while (l < r - 1)
    {
        int m = (l + r) / 2;
        if (a[m] < key)
        {
            l = m;
        }
        else
        {
            r = m;
        }

    }
    return r;
}
vector<long long> findLIS(vector<long long>& a)
{
    int n = a.size();
    vector<long long> d(n + 1, LLONG_MAX);
    vector<int> pos(n + 1);
    vector<int> prev(n);
    int length = 0;

    pos[0] = -1;
    d[0] = -LLONG_MAX;

    for (int i = 0; i < n; i++)
    {
        int j = binSearch(d, a[i]);
        if (d[j - 1] < a[i] && a[i] < d[j])
        {
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            length = max(length, j);
        }
    }

    vector<long long> answer;
    int p = pos[length];
    while (p != -1)
    {
        answer.push_back(a[p]);
        p = prev[p];
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

int main()
{
    int n;
    cin >> n;
    vector<long long> sequence;
    for (int i = 0; i < n; i++)
    {
        long long ai;
        cin >> ai;
        sequence.push_back(ai);
    }

    vector<long long> answer = findLIS(sequence);

    cout << answer.size() << "\n";
    for (int i = 0; i < answer.size(); i++)
    {
       cout << answer[i] << " ";
    }
    return 0;
}
