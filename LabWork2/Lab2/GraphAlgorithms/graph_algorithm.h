#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include<QVector>
#include<QString>
#include<QFile>
#include <algorithm>
#include <iterator>
//#include <gtest/gtest.h>
#include "graph.h"
#include "writeinfile.h"


const int COLORS_VECTOR_SIZE = 20; ///< Precise value of defined colors in COLORS_VECTOR, its size.
/**
* Defines different colors written in hexadecimal form in string type.
* Used for vertices coloring.
*/
const QVector<QString> COLORS_VECTOR{"#CA3434", "#E18A27", "#F6EE0D", "#11F60D", "#0DF6EA",
                                     "#0D66F6","#950DF6", "#F60DEE", "#66F60D", "#E3C2BF",
                                    "#C7BDBC","#91781B","#F4F984","#3FBF2B","#A3F4F0",
                                     "#18B3F0","#2034C9","#969FE2","#A573C8","#FD1A1E"};

/**
* Abstract class. Basic for number of graph algorithms classes.
* Contains graph, soucse vertex for algorithm, writeInFile object pointer
* responsible for writing every algorithm step into the file.
* Algorithm is considered to be executed by calling executeAlgorithm function.
* Destructor is virtual.
*/
class GraphAlgorithm
{
protected:
    const QString outputFile = QCoreApplication::applicationDirPath()+"//Files//output.txt";

    Graph graphInput;
    int s = 0; //source
    WriteInFile *writeFileHandler; //=NULL;
    const QString pathToFileResult = "C://QTProjectsMy//gAlgo//output.txt";
public:
    GraphAlgorithm(Graph &graph) : graphInput(graph){}
    virtual ~GraphAlgorithm() = default;
    virtual void executeAlgorithm() = 0;
    void setSourceVertex(int source);
};

/**
* Realize BFS (breadth first search) algorithm in iterative form.
* Derived from GraphAlgorithm class.
*/
class BFS : public GraphAlgorithm
{
public:
    BFS(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }
    BFS(Graph &graph, int source) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(source);
    }
    void executeAlgorithm();
private:
    //FRIEND_TEST(GraphAlgorithm, BFSTest);
};

/**
* Reailize DFS (depth first search) algorithm in iterative form.
* Derived from GraphAlgorithm class.
*/
class DFS : public GraphAlgorithm
{
public:
    DFS(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }
    DFS(Graph &graph, int source) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(source);
    }
    void executeAlgorithm();
private:
    //FRIEND_TEST(GraphAlgorithm, DFSTest);
};


/**
* Realize searching graph's connected components (for undirected)
* or strongly connected components (for directed).
* Marks each component with different colors.
* Based on DFS with maintainig not considered vertex' set.
* Derived from GraphAlgorithm class.
*/
class ConnectedComponents : public GraphAlgorithm
{
public:
    ConnectedComponents(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }
    ConnectedComponents(Graph &graph, int source) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(source);
    }
    void executeAlgorithm();

    QVector<int> findIntersection(QVector<int> &v1, QVector<int> &v2);


private:
   // FRIEND_TEST(GraphAlgorithm, ConnectedComponentsTest);
};

/**
* Coloring graph greedy algorithm.
* Do not use more than v+1 colors, where v is the biggest vertex' degree.
* Derived from GraphAlgorithm class.
*/
class ColorGraph: public GraphAlgorithm
{
public:
    ColorGraph(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }
    void executeAlgorithm();
private:
    //FRIEND_TEST(GraphAlgorithm, ColorGraphTest);
};

/**
* Detecting cycle algorithm using modified DFS.
* If DFS reach already marked as used vertex - the cycle is found,
* and algorithm stops working.
* Derived from GraphAlgorithm class.
*/
class DetectCycle: public GraphAlgorithm
{
public:
    DetectCycle(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteEdgeInFile(graph);
        setSourceVertex(0);
    }
    void executeAlgorithm();
private:
    //FRIEND_TEST(GraphAlgorithm, DetectCycleTest);
};


/**
* Only for unweighted graphs.
* Find shortest pathes from the sourse to all reachable other.
* Derived from GraphAlgorithm class.
*/
class ShortestPathes : public GraphAlgorithm
{
public:
    ShortestPathes (Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }
    ShortestPathes (Graph &graph, int source) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(source);
    }
    void executeAlgorithm();
private:


    //FRIEND_TEST(GraphAlgorithm, ShortestPathesTest);
};

/**
* Works only for weighted undirected connected graphs.
* Builds minimal spannin tree.
* Derived from GraphAlgorithm class.
* Using Prim's and Krauskal ideas.
* Visualize Krauskal algo.
*/
class MinimalSpanningTree: public GraphAlgorithm
{
public:
    MinimalSpanningTree(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteEdgeInFile (graph);
        setSourceVertex(0);
    }
    MinimalSpanningTree (Graph &graph, int source) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteEdgeInFile(graph);
        setSourceVertex(source);
    }
    void executeAlgorithm();
private:
    //FRIEND_TEST(GraphAlgorithm, MinimalSpanningTreeTest);
};


/**
* Derived from GraphAlgorithm class.
* Applied only to directed acyclic graphs.
* Use Kahn's algorithm.
*/
class TopologicalSortingKahnAlgorithm : public GraphAlgorithm
{
public:
    TopologicalSortingKahnAlgorithm(Graph &graph) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }

    void executeAlgorithm();
};


/**
* Derived from GraphAlgorithm class.
* Applied only to oriented graphs.
* Use Ford-Fulkerson algorithm.
* Throws an exception of QString type in case of use inappropriate graph to executeAlgorithm function.
*/
class MaximalFlowFromSource: public GraphAlgorithm
{
private:
    bool bfs(Graph &graphInput, int s, int t, QVector<int> &parent);
public:
    MaximalFlowFromSource (Graph &graph, int source = 0) : GraphAlgorithm (graph)
    {
        writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(source);
    }
    void executeAlgorithm();
private:
    //FRIEND_TEST(GraphAlgorithm, BFSTest);
};


#endif // GRAPH_ALGORITHM_H


