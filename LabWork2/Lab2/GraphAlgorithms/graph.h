#ifndef GRAPH_H
#define GRAPH_H

#include<QVector>
#include<QStack>
#include<QQueue>
#include<QtAlgorithms>

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
    void correctGraph(); ///< Makes graph matrix square and symmetric (if not oriented), delete loops.
    void transponse();

public:
    QVector<QVector<int>> graph;
    bool weighted = false;
    bool oriented = false;
    const int NO_EDGE = 0;
    const int INF = 99999; //random huge number less than weight of any graph edge

    Graph() = default;
    Graph(const QVector<QVector<int>> &graph, bool oriented, bool weighted);

    bool hasCycle() const;
    bool hasNegativeWeightEdge() const;
    QVector<int> BFSfrom(int source=0) const;
    QVector<int> DFSfrom(int source=0) const;
    bool isConnected();
    //bool hasNegativeWeightCycleDirectedGraph();
};

#endif // GRAPH_H
