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
    //writeInFile *fileHandler = NULL;
    //void shareAlgoStep()= 0;
public:
    GraphAlgorithm(Graph &graph) : graphInput(graph){}
};


class BFS : public GraphAlgorithm
{
public:
    BFS(Graph &graph) : GraphAlgorithm(graph){}
    void executeAlgorithm();
};

/*
class DFS : public GraphAlgorithm
{
public:
    DFS();
};
*/


#endif // GRAPH_ALGORITHM_H
