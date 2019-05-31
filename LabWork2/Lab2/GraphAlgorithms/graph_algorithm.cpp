#include <QQueue>
#include <QVector>
#include <QStack>
#include <QSet>
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
    QVector<bool> visited(sizeGraph, false);

    const int color = 0;// color number less than COLORS_VECTOR_SIZE
    QQueue<int> queue;
    visited[source] = true;
    queue.push_back(source);

    while(!queue.empty())
    {
        source = queue.front();
        writeFileHandler->write(new Vertex(source, COLORS_VECTOR[color]));
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
}


void DFS::executeAlgorithm()
{
    int source = s;
    int sizeGraph = graphInput.graph.size();
    const int color = 0; //color number less than COLORS_VECTOR_SIZE

    QVector<bool> visited(sizeGraph, false);
    QStack<int> stack;

    stack.push(source);
    while(!stack.empty())
    {
        source = stack.top();
        stack.pop();

        if (!visited[source])
        {
            writeFileHandler->write(new Vertex(source, COLORS_VECTOR[color]));
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


void ConnectedComponents::executeAlgorithm()
{
    int source = s; // get source vertex
    int sizeGraph = graphInput.graph.size(); //get size of graph

    QVector<bool> visited(sizeGraph, false); //visited vertices
    QStack<int> stack; //stack of current vertices to concern
    QVector<int> used(sizeGraph, false); //set of used vetrices

    int color = 0; // used as color identifier
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
                //writeOperation()
                std::cout<<source<<" "<<color;
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

        color++; //change color

        //find any still not used vertes (not from previous connectivity component)
        int indNotUsedVert = 0;
        for (; indNotUsedVert<sizeGraph; indNotUsedVert++)
        {
            if (!used[indNotUsedVert]) break;
        }
        if (indNotUsedVert==sizeGraph)
        {
            notAllVertUsed = false;
            //return;
        }
        stack.push(indNotUsedVert);
    }
}


void ColorGraph::executeAlgorithm()
{
    int sizeGraph = graphInput.graph.size(); //get size of graph
    QVector<int> resultVerticsColors(sizeGraph, -1);
    int source = 0;
    resultVerticsColors[source] = 0;
    //writeoperation
    QVector<bool> availableColors(sizeGraph, false);

    for (int u=1; u<sizeGraph; u++)
    {
        for (int adj_v = 0; adj_v < sizeGraph; adj_v++)
        {
            if (graphInput.graph[u][adj_v] != graphInput.NO_EDGE) //if an edge exists
            {
                if (resultVerticsColors[adj_v]!=-1)
                {
                    availableColors[resultVerticsColors[adj_v]] = true;
                }
            }
        }

        int cr;
        for (cr = 0; cr < sizeGraph; cr++)
        {
            if (availableColors[cr] == false) break;
        }
        resultVerticsColors[u] = cr;
        //writeOperation

        for (int adj_v = 0; adj_v < sizeGraph; adj_v++)
        {
            if (graphInput.graph[u][adj_v] != graphInput.NO_EDGE) //if an edge exists
            {
                if (resultVerticsColors[adj_v]!=-1)
                {
                    availableColors[resultVerticsColors[adj_v]] = false;
                }
            }
        }
    }
}

void DetectCycle::executeAlgorithm()
{
    int source = s; // get source vertex
    int sizeGraph = graphInput.graph.size(); //get size of graph

    QVector<bool> visited(sizeGraph, false); //visited vertices
    QStack<int> stack; //stack of current vertices to concern
    QVector<int> used(sizeGraph, false); //set of used vetrices

    int color = 0; // used as color identifier
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
                //writeOperation()
                std::cout<<source<<" "<<color;
                visited[source] = true;
            }
            else //has cycle
            {
                //writeOperation;
                return;
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

        color++; //change color

        //find any still not used vertes (not from previous connectivity component)
        int indNotUsedVert = 0;
        for (; indNotUsedVert<sizeGraph; indNotUsedVert++)
        {
            if (!used[indNotUsedVert]) break;
        }
        if (indNotUsedVert==sizeGraph)
        {
            notAllVertUsed = false;
            //return;
        }
        stack.push(indNotUsedVert);
    }
}

void ShortestPathes::executeAlgorithm()
{
    int sizeGraph = graphInput.graph.size();
    QVector<int> shortestDistancesFromS(sizeGraph, graphInput.INF);
    //QVector<int> prev(sizeGraph, -1); //have no previous vertices

    if (!graphInput.weighted) // start BFS from source
    {
        int source = s;
        int sizeGraph = graphInput.graph.size();
        QVector<bool> visited(sizeGraph, false);
        shortestDistancesFromS[source] = 0;

        QQueue<int> queue;
        visited[source] = true;
        queue.push_back(source);

        while(!queue.empty())
        {
            source = queue.front();
            //writeOperation; current distance to vertex
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
                        shortestDistancesFromS[adj_v] =  shortestDistancesFromS[source] + 1;
                        //prev[adj_v] = source;
                    }
                }
            }
        }

    }
    //else weighted
}
