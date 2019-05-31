#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include<QVector>
#include<QString>
#include "graph.h"
#include "writeinfile.h"

const int COLORS_VECTOR_SIZE = 10;
const QVector<QString> COLORS_VECTOR{"#CA3434", "#E18A27", "#F6EE0D", "#11F60D", "#0DF6EA",
                                     "#0D66F6","#950DF6", "#F60DEE", "#66F60D", "#E3C2BF"};

/**
* Abstract class.
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

class ConnectedComponents : public GraphAlgorithm
{
public:
    ConnectedComponents(Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    ConnectedComponents(Graph &graph, int source) : GraphAlgorithm (graph) {setSourceVertex(source);}
    void executeAlgorithm();
};


class ColorGraph: public GraphAlgorithm
{
public:
    ColorGraph(Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    void executeAlgorithm();
};


class DetectCycle: public GraphAlgorithm
{
public:
    DetectCycle(Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    void executeAlgorithm();
};


/**
* Only for unweighted graphs.
*/
class ShortestPathes : public GraphAlgorithm
{
public:
    ShortestPathes (Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    ShortestPathes (Graph &graph, int source) : GraphAlgorithm (graph) {setSourceVertex(source);}
    void executeAlgorithm();
};


#endif // GRAPH_ALGORITHM_H
