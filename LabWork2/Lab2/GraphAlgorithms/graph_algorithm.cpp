#include <QQueue>
#include <QVector>
#include <QStack>
#include "graph_algorithm.h"

#include<iostream>

void GraphAlgorithm::setSourceVertex(int source)
{
    int sizeGraph = graphInput.graph.size();
    if (source>=sizeGraph || source<0)
    {
        s = 0;
        return;
    }

    s = source; //return;
}

void BFS::executeAlgorithm()
{
    int source = s;
    int sizeGraph = graphInput.graph.size();
    bool *visited = new bool[sizeGraph];
    for (int i=0; i<sizeGraph; i++)
    {
        visited[i] = false;
    }

    QQueue<int> queue;
    visited[source] = true;
    queue.push_back(source);

    while(!queue.empty())
    {
        source = queue.front();
        //writeOperation;
        std::cout<<source; //debugiing

        queue.pop_front();

        for (int adj_v = 0; adj_v < sizeGraph; adj_v++)
        {
            if (graphInput.graph[source][adj_v] != graphInput.NO_EDGE) //if an edge exists
            {
                if (!visited[adj_v]) // if still not visited
                {
                    visited[adj_v] = true;
                    queue.push_back(adj_v);
                }
            }
        }
    }

    delete [] visited;
}


void DFS::executeAlgorithm()
{
    int source = s;
    int sizeGraph = graphInput.graph.size();

    QVector<bool> visited(sizeGraph, false);

    QStack<int> stack;

    stack.push(source);
    while(!stack.empty())
    {
        source = stack.top();
        stack.pop();

        if (!visited[source])
        {
            //writeOperation()
            std::cout<<source;
            visited[source] = true;
        }

        for (int adj_v = 0; adj_v < sizeGraph; adj_v++)
        {
            if (graphInput.graph[source][adj_v] != graphInput.NO_EDGE) //if an edge exists
            {
                if (!visited[adj_v]) // if still not visited
                {
                   stack.push(adj_v);
                }
            }
        }
    }

}




