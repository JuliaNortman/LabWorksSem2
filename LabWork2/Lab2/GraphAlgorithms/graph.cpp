#include "graph.h"

bool Graph::isCorrectGraph() const
{
    if (!hasSquareMatrix()) return false;
    if (hasLoops()) return false;

    if (!oriented)
    {
        if (!hasSymmectricMatrix()) return false;
    }

    return true;
}

bool Graph::hasLoops() const
{
    if (!hasSquareMatrix()) return false;

    int s = graph.size();
    for (int i=0; i<s; i++)
    {
        if (graph[i][i]!=0) return true;
    }

    return false;
}

bool Graph::hasSymmectricMatrix() const
{
    if (!hasSquareMatrix()) return false;

    int s = graph.size();
    for (int i=0; i<s; i++)
        for (int j=0; j<s; j++)
        {
            if (graph[i][j] != graph[j][i]) return false;
        }

    return true;
}

bool Graph::hasSquareMatrix() const
{
    int s = graph.size();
    for (int i=0; i<s; i++)
    {
        if (s != graph[i].size()) return false;
    }

    return true;
}

void Graph::deleteLoops()
{
    if (hasSquareMatrix())
    {
        int s = graph.size();
        for (int i=0; i<s; i++)
            graph[i][i] = 0;
    }
}
