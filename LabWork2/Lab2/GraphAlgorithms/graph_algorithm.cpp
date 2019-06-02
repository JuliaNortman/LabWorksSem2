#include <QQueue>
#include <QVector>
#include <QStack>
#include <QSet>
#include <QMap>
#include <QPair>
#include <map>
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
    QVector<int> BFSTraverseResult; //contains vertex sequence

    const int color = 0;// color number less than COLORS_VECTOR_SIZE
    QQueue<int> queue;
    visited[source] = true;
    queue.push_back(source);

    while(!queue.empty())
    {
        source = queue.front();
        BFSTraverseResult.push_back(source);
        writeFileHandler->write(new Vertex(source, COLORS_VECTOR[color]));
        std::cout << source << " ";
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


    QString result;
    for (int i=0; i<BFSTraverseResult.size(); i++)
    {
        result += QString::number(BFSTraverseResult[i]) + " ";
    }
    QFile file (pathToFileResult);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    file.write(result.toStdString().c_str());
    file.close();
}


void DFS::executeAlgorithm()
{
    int source = s;
    int sizeGraph = graphInput.graph.size();
    const int color = 0; //color number less than COLORS_VECTOR_SIZE

    QVector<int> DFSTraverseResult; //contains vertex sequence
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
            DFSTraverseResult.push_back(source);
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

    //writing result into the file
    QString result;
    for (int i=0; i<DFSTraverseResult.size(); i++)
    {
        result += QString::number(DFSTraverseResult[i]) + " ";
    }
    QFile file (pathToFileResult);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    file.write(result.toStdString().c_str());
    file.close();

}


void ConnectedComponents::executeAlgorithm()
{
    int source = s; // get source vertex
    int sizeGraph = graphInput.graph.size(); //get size of graph

    QVector<bool> visited(sizeGraph, false); //visited vertices
    QStack<int> stack; //stack of current vertices to concern
    QVector<int> used(sizeGraph, false); //set of used vetrices

    QString connectedComponents; //contains sequences of vertics (components) devided by commas

    bool notAllVertUsed = true;
    stack.push(source);
    int color = 0; //color number less than COLORS_VECTOR_SIZE
    while(notAllVertUsed)
    {
        if (source!=s){connectedComponents += "| ";} //if not first component then add a devider

        while(!stack.empty())
        {
            source = stack.top();
            stack.pop();
            used[source] = true;

            if (!visited[source])
            {
                writeFileHandler->write(new Vertex(source, COLORS_VECTOR[color%COLORS_VECTOR_SIZE]));
                connectedComponents += QString::number(source) + " ";
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

    //writing into the file
    QFile file (pathToFileResult);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    file.write(connectedComponents.toStdString().c_str());
    file.close();
}


void ColorGraph::executeAlgorithm()
{
    int sizeGraph = graphInput.graph.size(); //get size of graph
    QVector<int> resultVerticsColors(sizeGraph, -1);
    int source = 0;
    resultVerticsColors[source] = 0;

    QFile file (pathToFileResult);
    file.open(QIODevice::WriteOnly); //open file
    file.write((QString::number(source) + " of color " + "0\n").toStdString().c_str());

    writeFileHandler->write(new Vertex(source, COLORS_VECTOR[0])); //write in file operation
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
        writeFileHandler->write(new Vertex(u, COLORS_VECTOR[cr%COLORS_VECTOR_SIZE])); //safe write in file operation
        file.write((QString::number(u) + " of color " + QString::number(cr) + " \n").toStdString().c_str());

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

    file.close();
}

void DetectCycle::executeAlgorithm()
{
    int source = s; // get source vertex
    int sizeGraph = graphInput.graph.size(); //get size of graph

    QVector<bool> visited(sizeGraph, false); //visited vertices
    QStack<int> stack; //stack of current vertices to concern
    QVector<int> used(sizeGraph, false); //set of used vetrices

    QFile file (pathToFileResult);
    file.open(QIODevice::WriteOnly); //open file

    int color = 0; // used as color identifier

    QVector<int> previous(sizeGraph, -1);
    bool notAllVertUsed = true;
    stack.push(source);
    while(notAllVertUsed)
    {
        bool newComponent = true;
        int previousSource = -1;

        while(!stack.empty())
        {
            source = stack.top();
            stack.pop();
            used[source] = true;

            if (!visited[source])
            {
                visited[source] = true;
                if (!newComponent)
                {
                    writeFileHandler->write(new Edge(source, previous[source], COLORS_VECTOR[color]));
                    file.write((QString::number(previous[source]) + "--" + QString::number(source)+ "\n").toStdString().c_str());
                }
            }
            else //has cycle
            {
                for (int i=0; i<sizeGraph; i++)
                {
                    if ((graphInput.graph[source][i] != graphInput.NO_EDGE) && (previous[source]!=i) && visited[i])
                    {
                       writeFileHandler->write(new Edge(i, source, COLORS_VECTOR[++color]));
                       file.write((QString::number(source) +"--"+ QString::number(i) + "\nCYCLE FOUND").toStdString().c_str());
                       file.close();
                       return;
                    }
                }
            }

            for (int adj_v = 0; adj_v < sizeGraph; adj_v++)
            {
                if (graphInput.graph[source][adj_v] != graphInput.NO_EDGE) //if an edge exists
                {
                    if (!visited[adj_v]) // if still not visited
                    {
                        stack.push(adj_v);
                        previous[adj_v] = source;
                    }
                    else if (visited[adj_v] && graphInput.oriented) //cycle found
                    {
                        writeFileHandler->write(new Edge(adj_v, source, COLORS_VECTOR[++color]));
                        file.write((QString::number(source) + "--" + QString::number(adj_v) + "\nCYCLE FOUND").toStdString().c_str());
                        file.close();
                        return;
                    }
                }
            }
            newComponent = false;
            previousSource = source;
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

    file.write("\n| CYCLE NOT DETECTED |");
    file.close();
}

void ShortestPathes::executeAlgorithm()
{
    int sizeGraph = graphInput.graph.size();
    QVector<int> shortestDistancesFromS(sizeGraph, graphInput.INF);
    shortestDistancesFromS[s] = 0;
    const int color = 0;

    if (!graphInput.weighted) // start BFS from source
    {
        int source = s;
        QVector<bool> visited(sizeGraph, false);

        QQueue<int> queue;
        visited[source] = true;
        queue.push_back(source);

        while(!queue.empty())
        {
            source = queue.front();
            writeFileHandler->write(new Vertex(source, COLORS_VECTOR[color], shortestDistancesFromS[source]));
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
    else
    {
        throw "NOT APPLIED TO SUCH A GRAPH";
    }

    //preparing and writing result file
    QString result;
    for (int i = 0; i < shortestDistancesFromS.size(); i++)
    {
        if ((shortestDistancesFromS[i] != graphInput.INF) && (i!=s))
        {
            result += QString::number(s) + "-->" + QString::number(i) + " : " + QString::number(shortestDistancesFromS[i]) + " \n";
        }
    }

    QFile file (pathToFileResult);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    file.write(result.toStdString().c_str());
    file.close();
}


void MinimalSpanningTree::executeAlgorithm()
{
    if (!graphInput.isConnected() || graphInput.oriented || !graphInput.weighted)
    {
        const QString str = "NOT APPLIED TO SUCH A GRAPH";
        throw str;
        //return;
    }
    //else

    int sizeGraph = graphInput.graph.size();
    QVector<int> parent(sizeGraph);
    QVector<int> key(sizeGraph, graphInput.INF);
    QVector<bool> mstSet (sizeGraph, false);

    int source = 0;
    key[source] = 0;
    parent[source] = -1;

    int min = graphInput.INF; int min_index;

    for (int i = 0; i< sizeGraph-1; i++)
        {
            min = graphInput.INF;
            for (int v = 0; v < sizeGraph; v++)
                if (mstSet[v] == false && key[v] < min)
                {
                    min = key[v];
                    min_index = v;
                }
            int u = min_index;

            mstSet[u] = true;
            for (int v = 0; v < sizeGraph; v++)
                {
                    if (graphInput.graph[u][v] && mstSet[v] == false && graphInput.graph[u][v] < key[v])
                    {
                        parent[v] = u;
                        key[v] = graphInput.graph[u][v];
                    }
                }
        }

    //got spanning tree and prepare it to step visualizaion
   std::multimap<int, std::pair<int,int>> minTree;
    for (int i = 1; i < sizeGraph; i++)
        {
            //std::cout <<  parent[i] << "---" << i << "   " <<graphInput.graph[i][parent[i]] << std::endl;
            minTree.insert(std::pair<int, std::pair<int,int>> (graphInput.graph[i][parent[i]], std::pair<int,int>(parent[i],i)));
        }


    QFile file (pathToFileResult);
    file.open(QIODevice::WriteOnly); //open file to put result in
    int color = 0;
    std::multimap<int, std::pair<int,int>>::iterator it = minTree.begin();
    for (;it!=minTree.end(); it++)
    {
        writeFileHandler->write(new Edge(it->second.second, it->second.first, COLORS_VECTOR[color], it->first));
        writeFileHandler->write(new Edge(it->second.first, it->second.second, COLORS_VECTOR[color], it->first));
        file.write((QString::number(it->second.first) + "--" + QString::number(it->second.second) + " \n").toStdString().c_str());
    }

    file.close();
}

