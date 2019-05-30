#include <QQueue>
#include "graph_algorithm.h"

#include<iostream>

void BFS::executeAlgorithm()
{
    int source = 0;
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
