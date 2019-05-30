#include "graph.h"

Graph::Graph(const QVector<QVector<int>> &graph, bool oriented, bool weighted)
{
    this->graph = graph;
    this->oriented = oriented;
    this->weighted = weighted;
    if (!isCorrectGraph())
    {
        correctGraph();
    }
}


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

void Graph::correctGraph()
{
    int largestDimention = graph.size();
    for (auto v : graph)                    ///< Getting largest dimention of the table (still not matrix).
    {
        if (v.size() > largestDimention)
        {
            largestDimention = v.size();
        }
    }

    graph.resize(largestDimention);  ///< Making matrix square and filling new cells with NO_EDGE.
    for (auto v : graph)
    {
        while(v.size() != largestDimention)
        {
            v.push_back(NO_EDGE);
        }
    }

    deleteLoops(); ///< According to the conditions loops do not exist, so delete them.

    if (!oriented)              ///< If oriented, matrix is symmetric.
    {                           ///< Refletcting elements of upper-right triangle relatively to main diagonal.
        for (int i=0; i<graph.size(); i++)
            for (int j=0; j<graph.size(); j++)
                graph[j][i] = graph[i][j];
    }
}


bool Graph::hasCycle() const
{
    int source = 0; // get source vertex
    int sizeGraph = graph.size(); //get size of graph

    QVector<bool> visited(sizeGraph, false); //visited vertices
    QStack<int> stack; //stack of current vertices to concern
    QVector<int> used(sizeGraph, false); //set of used vetrices

    bool notAllVertUsed = true;
    stack.push(source);
    while(notAllVertUsed)
    {
        while(!stack.empty())
        {
            source = stack.top();
            stack.pop();
            used[source] = true;

            if (!visited[source])
            {
                visited[source] = true;
            }
            else
            {
                return true;
            }

            for (int adj_v = 0; adj_v < sizeGraph; adj_v++)
            {
                if (graph[source][adj_v] != NO_EDGE) //if an edge exists
                {
                    if (!visited[adj_v]) // if still not visited
                    {
                       stack.push(adj_v);
                    }
                }
            }
        }

        //find any still not used vertes (not from previous connectivity component)
        int indNotUsedVert = 0;
        for (; indNotUsedVert<sizeGraph; indNotUsedVert++)
        {
            if (!used[indNotUsedVert]) break;
        }
        if (indNotUsedVert==sizeGraph)
        {
            return false;
        }
        stack.push(indNotUsedVert);
    }

    return false;
}

bool Graph::hasNegativeWeightEdge() const
{
    for (auto row : graph)
        for (auto elem : row)
            if (elem<0 && elem!=NO_EDGE) return true;
    return false;
}
