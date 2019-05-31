#ifndef GRAPH_H
#define GRAPH_H

#include<QVector>
#include<QStack>
#include<QQueue>
#include<QtAlgorithms>

/**
* Whatever matrix it be, it can be interpretated as a graph.
* Graph is QVector<QVector<int>>.
* Constructor cheks if graph is oriented and weighted and corrects its matrix in case of need.
*/
class Graph
{
private:
    bool isCorrectGraph() const;  ///< Checks matrix graph to be square and symmetric in case of undirectedness, checks for loops.
    bool hasLoops() const;        ///< Checks if square matrix has any loop.
    bool hasSymmectricMatrix() const;     ///< Checking square matrix to be symmetric.
    bool hasSquareMatrix() const;         ///< Checks for squareness.
    void deleteLoops();                   ///< Sets main diagonal elements equal to NO_EDGE value.
    void correctGraph();                  ///< Makes graph matrix square and symmetric (if not oriented), delete loops.
    void transponse();                    ///< Transpose square matrix.

public:
    QVector<QVector<int>> graph;          ///< Graphs adjacency matrix.
    bool weighted = false;                ///< Mean if graph weighted (elements not obviously == 0).
    bool oriented = false;                ///< If graph oriented. (matrix not obviously symmetric).
    const int NO_EDGE = 0;                ///< Const to mark elements with no edges between them.
    const int INF = 99999;                ///< Special value for some algos. Huge positive integer. Bigger than any enge weight.

    Graph() = default;                    ///< Leave default constructor.
    Graph(const QVector<QVector<int>> &graph, bool oriented, bool weighted); ///< Creates new graph from matrix, and grpahs params.

    bool hasCycle() const;                    ///< Check with DFS for cycles.
    bool hasNegativeWeightEdge() const;       ///< Checks for negative values in the matrix.
    QVector<int> BFSfrom(int source=0) const; ///< Returns BFS traverse vector.
    QVector<int> DFSfrom(int source=0) const; ///< Returns DFS traverse vector.
    bool isConnected();                       ///< Checks graph to be connected (with BFS) or strongly connected (for oriented use DFS).
    //bool hasNegativeWeightCycleDirectedGraph();
};

#endif // GRAPH_H
