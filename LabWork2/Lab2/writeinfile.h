#ifndef WRITEINFILE_H
#define WRITEINFILE_H

#include <QObject>
#include <QVector>
#include <QFile>

//test, should be deleted
class Graph
{
private:


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

    const int NO_EDGE = 0;
};

class Data
{
public:
    QString label; //additional mark on the vertex
    QString color; //color in which vertex will be printed
};

class Vertex :public Data
{
public:
    QString vertex;
};

class Edge :public Data
{
public:
    QString from; //start of the edge
    QString to; //end of the edge
};

class WriteInFile
{
public:
    WriteInFile(const Graph& G);
    virtual ~WriteInFile() = default;
    virtual void write(const Vertex&) = 0;
};

/*class WriteEdgeInFile :public WriteInFile
{
public:
    void write(const Edge&);
};*/

class WriteVertexInFile :public WriteInFile
{
public:
    WriteVertexInFile(const Graph& G): WriteInFile(G){}
    void write(const Vertex&);
};

#endif // WRITEINFILE_H
