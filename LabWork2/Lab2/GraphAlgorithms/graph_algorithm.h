#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include "graph.h"


/**
* Abstract class.
*/
class GraphAlgorithm
{
protected:
    Graph graphInput;
    int s = 0; //source
    //writeInFile *fileHandler = NULL;
    //virtual void shareAlgoStep()= 0;
    void setSourceVertex(int source);
public:
    GraphAlgorithm(Graph &graph) : graphInput(graph){}
    virtual void executeAlgorithm() = 0;
};


class BFS : public GraphAlgorithm
{
public:
    BFS(Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    BFS(Graph &graph, int source) : GraphAlgorithm (graph) {setSourceVertex(source);}
    void executeAlgorithm();
};


class DFS : public GraphAlgorithm
{
public:
    DFS(Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    DFS(Graph &graph, int source) : GraphAlgorithm (graph) {setSourceVertex(source);}
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

/*
class ShortestPathes : public GraphAlgorithm
{
public:
    ShortestPathes (Graph &graph) : GraphAlgorithm (graph) {setSourceVertex(0);}
    ShortestPathes (Graph &graph, int source) : GraphAlgorithm (graph) {setSourceVertex(source);}
    void executeAlgorithm();
};
*/

#endif // GRAPH_ALGORITHM_H
