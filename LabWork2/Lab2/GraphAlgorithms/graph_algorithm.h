#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include<QVector>
#include<QString>
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
    Graph graphInput;
    int s = 0; //source
    WriteInFile *writeFileHandler; //=NULL;
    void setSourceVertex(int source);
public:
    GraphAlgorithm(Graph &graph) : graphInput(graph){}
    virtual ~GraphAlgorithm() = default;
    virtual void executeAlgorithm() = 0;
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
        //writeFileHandler = new WriteVertexInFile (graph);
        setSourceVertex(0);
    }
    void executeAlgorithm();
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
};

#endif // GRAPH_ALGORITHM_H
