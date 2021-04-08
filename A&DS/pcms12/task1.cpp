#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
 
vector<int> findLIS(vector<int>& a)
{
    int n = a.size();
    vector<int> prev(n, -1);
    vector<int> d(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i] && d[j] + 1 > d[i])
            {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
        }
    }
 
    int pos = 0;
    int length = d[0];
    for (int i = 0; i < n; i++)
    {
        if (d[i] > length)
        {
            pos = i;
            length = d[i];
        }
    }
    vector<int> answer;
    while (pos != -1)
    {
        answer.push_back(a[pos]);
        pos = prev[pos];
    }
    reverse(answer.begin(), answer.end());
    return answer;
}
 
int main()
{
    int n;
    cin >> n;
    vector<int> sequence;
    for (int i = 0; i < n; i++)
    {
        int ai;
        cin >> ai;
        sequence.push_back(ai);
    }
 
    vector<int> answer = findLIS(sequence);
 
    cout << answer.size() << "\n";
    for (int i = 0; i < answer.size(); i++)
    {
       cout << answer[i] << " ";
    }
    return 0;
}