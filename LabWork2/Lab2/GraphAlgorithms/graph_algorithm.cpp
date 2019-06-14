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
    if (!graphInput.isCorrectGraph())
    {
        const QString str = "INCORRECT GRAPH";
        throw str;
        //return;
    }

    int source = s;
    int sizeGraph = graphInput.graph.size();
    QVector<bool> visited(sizeGraph, false);
    QVector<int> BFSTraverseResult; //contains vertex sequence

    const int color = 0;// color number less than COLORS_VECTOR_SIZE
    QQueue<int> queue;
    //visited[source] = true;
    //queue.push_back(source);
    for (int j=0; j<sizeGraph;j++)
    {
        int i = (j + s)%sizeGraph;

        if (!visited[i])
        {
            /*if (i == s)*/visited[i] = true;
            queue.push_back(i);
            while(!queue.empty())
            {
                source = queue.front();
                BFSTraverseResult.push_back(source);
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
    if (!graphInput.isCorrectGraph())
    {
        const QString str = "INCORRECT GRAPH";
        throw str;
        //return;
    }

    int source = s;
    int sizeGraph = graphInput.graph.size();
    const int color = 0; //color number less than COLORS_VECTOR_SIZE

    QVector<int> DFSTraverseResult; //contains vertex sequence
    QVector<bool> visited(sizeGraph, false);
    QStack<int> stack;

    for (int j = 0; j<sizeGraph; j++)
    {
        int i=(j+s)%sizeGraph;
        if (!visited[i])
        {
            stack.push(i);
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


QVector<int> ConnectedComponents::findIntersection(QVector<int> &v1, QVector<int> &v2)
{
        QVector<int> v_intersection;

        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());

        std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                                  std::back_inserter(v_intersection));
        return v_intersection;

}

void ConnectedComponents::executeAlgorithm()
{
    int source = s; // get source vertex
    int sizeGraph = graphInput.graph.size(); //get size of graph

    if (!graphInput.oriented)
    {
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
    else //if oriented
    {
        QVector<int> dfsResult;
        QVector<int> dfsReverseResult;
        QVector<QVector<int>> stronglyConnectedComponents;
        QVector<int> intersection;
        QVector<int> used(sizeGraph, false);
        for (int v = 0; v < sizeGraph; v++)
        {
            if (!used[v])
            {
                dfsResult = graphInput.DFSfrom(v);
                graphInput.transponse();
                dfsReverseResult = graphInput.DFSfrom(v);
                graphInput.transponse(); // set matrix back to initial state
                intersection = findIntersection(dfsResult, dfsReverseResult);
                for (int i=0; i<intersection.size(); i++)
                {
                    used[i] = true;
                }

                stronglyConnectedComponents.push_back(intersection);
            }
        }

        int color = 0;
        QFile file(pathToFileResult);
        file.open(QIODevice::WriteOnly);

        for (int i=0; i<stronglyConnectedComponents.size(); i++)
        {
            for (int j=0; j<stronglyConnectedComponents[i].size(); j++)
            {
                file.write((QString::number(stronglyConnectedComponents[i][j]) + " ").toStdString().c_str());
                writeFileHandler->write(new Vertex(stronglyConnectedComponents[i][j], COLORS_VECTOR[color%COLORS_VECTOR_SIZE]));
            }
            color++;
            file.write(("|\n"));
        }
        file.close();

    }
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
    else //use Bellman-Ford algorithm for weighted graphs
    {
        //preparing graph
        for(int i=0; i<sizeGraph; i++)
            for (int j=0; j<sizeGraph; j++)
                if (graphInput.graph[i][j] == graphInput.NO_EDGE)
                {
                    graphInput.graph[i][j] =  graphInput.INF;
                }

        for (int i=1; i<=sizeGraph-1; i++)
        {
            for (int j=0; j<sizeGraph; j++)
            {
                for(int k=0; k<sizeGraph; k++)
                {
                    if (j!=k && graphInput.graph[j][k]!=graphInput.INF)
                    {
                        if (shortestDistancesFromS[j] != graphInput.INF && shortestDistancesFromS[j] + graphInput.graph[j][k] < shortestDistancesFromS[k])
                        {
                            shortestDistancesFromS[k] = shortestDistancesFromS[j] + graphInput.graph[j][k];
                        }
                    }
                }
            }
        }

        //visualization
        writeFileHandler->write(new Vertex(s, COLORS_VECTOR[color], 0)); //writing source vertex with distance 0
        for (int i=0; i<sizeGraph; i++)
        {
            if (shortestDistancesFromS[i] == graphInput.INF || i==s) continue;
            writeFileHandler->write(new Vertex(i, COLORS_VECTOR[color], shortestDistancesFromS[i]));
        }

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

    if (graphInput.weighted)
    {
        //check for negative cycle
        for (int i=0; i<sizeGraph; i++)
        {
            for (int j=0; j<sizeGraph; j++)
            {
                if (j!=i && graphInput.graph[i][j]!=graphInput.INF)
                {
                    if (shortestDistancesFromS[i]!=graphInput.INF && shortestDistancesFromS[i] + graphInput.graph[i][j] < shortestDistancesFromS[j])
                    {
                        file.write("NEGATIVE CYCLE FOUND, SOME SHORTEST PATHES ARE INCORRECT");
                    }
                }
            }
        }
    }

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
        writeFileHandler->write(new Edge(it->second.first, it->second.second, COLORS_VECTOR[color], it->first));
        //writeFileHandler->write(new Edge(it->second.first, it->second.second, COLORS_VECTOR[color], it->first));
        file.write((QString::number(it->second.first) + "--" + QString::number(it->second.second) + " \n").toStdString().c_str());
    }

    file.close();
}



//-------------------------------------------
void DetectCycle::executeAlgorithm()
{
    int source = s; // get source vertex
    int sizeGraph = graphInput.graph.size(); //get size of graph

    QVector<bool> visited(sizeGraph, false); //visited vertices
    QStack<int> stack; //stack of current vertices to concern
    QVector<int> used(sizeGraph, false); //set of used vetrices
    QVector<int> componentOfVertex(sizeGraph, -1);

    QFile file (pathToFileResult);
    file.open(QIODevice::WriteOnly); //open file

    int color = 0; // used as color identifier

    QVector<int> previous(sizeGraph, -1);
    bool notAllVertUsed = true;
    stack.push(source);

    int component = 0;
    while(notAllVertUsed)
    {
        bool newComponent = true;
        int previousSource = -1;

        while(!stack.empty())
        {
            source = stack.top();
            stack.pop();
            used[source] = true;
            componentOfVertex[source] = component;

            if (!visited[source])
            {
                visited[source] = true;
                if (!newComponent)
                {
                    writeFileHandler->write(new Edge(previous[source], source, COLORS_VECTOR[color]));
                    file.write((QString::number(previous[source]) + "--" + QString::number(source)+ "\n").toStdString().c_str());
                }
            }
            else //has cycle
            {
                for (int i=0; i<sizeGraph; i++)
                {
                    if ((graphInput.graph[source][i] != graphInput.NO_EDGE) && (previous[source]!=i) && visited[i])
                    {
                       writeFileHandler->write(new Edge(source, i, COLORS_VECTOR[++color]));
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
                    else if (visited[adj_v] && graphInput.oriented && (componentOfVertex[source]==componentOfVertex[adj_v])
                             && (previous[source]==previousSource)) //cycle found
                    {
                        writeFileHandler->write(new Edge(source, adj_v, COLORS_VECTOR[++color]));
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
        component++;

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


//works only with NOT CYCLIC DIRECTED graphs
void TopologicalSortingKahnAlgorithm::executeAlgorithm()
{
    if (!graphInput.oriented)
    {
        const QString str = "NOT APPLIED TO SUCH A GRAPH";
        throw str;
    }
    //else
    int sizeGraph = graphInput.graph.size();
    QVector<int> inDegree(sizeGraph, 0);

    for (int u=0; u < sizeGraph; u++)
    {
        for (int adjV = 0; adjV < sizeGraph; adjV++)
        {
            if (graphInput.graph[u][adjV] != graphInput.NO_EDGE)
            {
                inDegree[adjV]++;
            }
        }
    }

      QQueue<int> q;
      for (int i = 0; i < sizeGraph; i++)
          if (inDegree[i] == 0)
              q.push_back(i);

       int cnt = 0;

      QVector <int> top_order;

      // One by one dequeue vertices from queue and enqueue
      // adjacents if indegree of adjacent becomes 0
      while (!q.empty())
      {
          int u = q.front();
          q.pop_front();
          top_order.push_back(u);

          for (int adj = 0; adj < sizeGraph; adj++)
          {
              if (graphInput.graph[u][adj] != graphInput.NO_EDGE)
              {
                  if (--inDegree[adj] == 0)
                      q.push_back(adj);
              }
          }
          cnt++;
      }

      QFile file (pathToFileResult);
      file.open(QIODevice::WriteOnly);

      if(top_order.size() != sizeGraph)
      {
          file.write("GRAPH HAS A CYCLE\nAlgorithm not applied to such graphs");
          return;
      }

      for (int i=0; i<top_order.size(); i++)
      {
          //std::cout<<top_order[i] << " ";
          writeFileHandler->write(new Vertex(top_order[i], COLORS_VECTOR[0], i));
          file.write((QString::number(top_order[i]) + " - ").toStdString().c_str());
      }
      file.close();
}


bool MaximalFlowFromSource::bfs(Graph &graphInput, int s, int t, QVector<int> &parent)
{
    int sizeGraph = graphInput.graph.size();
    QVector<bool> visited (sizeGraph, false);

    QQueue <int> q;
    q.push_back(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();

        for (int v=0; v<sizeGraph; v++)
        {
            if (visited[v]==false && graphInput.graph[u][v] > 0)
            {
                q.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

void MaximalFlowFromSource::executeAlgorithm()
{
    if (!graphInput.oriented)
    {
         const QString str = "NOT APPLIED TO SUCH A GRAPH";
         throw str;
    }

    int sizeGraph = graphInput.graph.size();
    QVector<int> ResultFlowFromSTodest;
    int dest = (s+1)% sizeGraph;
    int color = 0;
    writeFileHandler->write(new Vertex(s, COLORS_VECTOR[color])); //colored source vertex
    color++; //changed color
    if (sizeGraph == 1) return;

    //for each vertex start fordFulkerson algo
    do
    {
        Graph *g = new Graph(graphInput.graph, graphInput.oriented, graphInput.weighted);
        QVector<int> parent(sizeGraph);
        int maxFlowResult = 0;

        while(bfs(*g, s, dest, parent))
        {
            int pathFlow = graphInput.INF; //or int_max
            for (int v=dest; v!=s; v=parent[v])
                {
                    int u = parent[v];
                    pathFlow = std::min(pathFlow, g->graph[u][v]);
                }

             for (int v=dest; v != s; v=parent[v])
                {
                    int u = parent[v];
                    g->graph[u][v] -= pathFlow;
                    g->graph[v][u] += pathFlow;
                }

             // Add path flow to overall flow
             maxFlowResult += pathFlow;
        }

        ResultFlowFromSTodest.push_back(maxFlowResult); //writing max flow from source to (s+1+iteration)%size in (iteration) cell
                                                        //counting from zero
        delete g; //free memory
        writeFileHandler->write(new Vertex(dest, COLORS_VECTOR[0], maxFlowResult));
        dest = (dest+1)%sizeGraph;
    }
    while(dest!=s);

    //writing file
    QFile file (pathToFileResult);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    for (int i=0; i<sizeGraph-1; i++)
    {
        file.write((QString::number(s) + "->" + QString::number((s+i+1)%sizeGraph)+ " : " + QString::number(ResultFlowFromSTodest[i]) + "\n").toStdString().c_str());
    }
    file.close();
}
