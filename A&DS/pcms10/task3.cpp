#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Edge
{
public:
    int startNode;
    int endNode;
    int lenght;
    Edge(int startNode_, int endNode_, int lenght_)
    {
        startNode = startNode_;
        endNode = endNode_;
        lenght = lenght_;
    }
};

int findComponent(int node, vector<int>& components)
{
    if (components[node]  == node)
    {
        return node;
    }
    return findComponent(components[node], components);

}

bool sameComponent(int node1, int node2, vector<int>& components)
{
    return findComponent(node1, components) == findComponent(node2, components);
}

void uniteToOneComponent(int node1, int node2, vector<int>& components, vector<int>& sizeOfComponents)
{
    node1 = findComponent(node1, components);
    node2 = findComponent(node2, components);
    if (sizeOfComponents[node1] >= sizeOfComponents[node2])
    {
        swap(node1, node2);
    }
    sizeOfComponents[node2] += sizeOfComponents[node1];
    components[node1] = node2;
}

int main()
{
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");

    int numOfNodes, numOfEdges;
    long long answer = 0;

    fin >> numOfNodes >> numOfEdges;

    vector<Edge> Edges;
    vector<int> components(numOfNodes);
    vector<int> sizeOfComponents(numOfNodes, 1);

    for (int i = 0; i < numOfNodes; i++)
    {
        components[i] = i;
    }

    for (int i = 0; i < numOfEdges; i++)
    {
        int v1, v2, w;
        fin >> v1 >> v2 >> w;
        Edges.emplace_back(Edge(v1 - 1, v2 - 1, w));
    }

    sort(Edges.begin(), Edges.end(), [](const Edge &left, const Edge &right)
    {
        return left.lenght < right.lenght;
    });

    for (int i = 0; i < Edges.size(); i++)
    {
        if (!sameComponent(Edges[i].startNode, Edges[i].endNode, components))
        {
            uniteToOneComponent(Edges[i].startNode, Edges[i].endNode, components, sizeOfComponents);
            answer += Edges[i].lenght;
        }
    }
    fout << answer;
    return 0;
}
