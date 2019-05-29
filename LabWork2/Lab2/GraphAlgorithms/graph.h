#ifndef GRAPH_H
#define GRAPH_H

#include<QVector>

/**
* Whatever matrix it be, it can be interpretated as a graph.
*/
class Graph
{
private:
    bool isCorrectGraph() const;
    bool hasLoops() const;
    bool hasSymmectricMatrix() const;
    bool hasSquareMatrix() const;
    void deleteLoops();

public:
    QVector<QVector<int>> graph;
    bool weighted = false;
    bool oriented = false;

    Graph() = default;
    Graph(const QVector<QVector<int>> &graph, bool oriented, bool weighted)
    {
        this->graph = graph;
        this->oriented = oriented;
        this->weighted = weighted;
    }

    //void autoCompleteGraph();

};

#endif // GRAPH_H
