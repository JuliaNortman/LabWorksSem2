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



class Vertex
{
public:
    Vertex(int v, QString color, int label = 0);
    QString label; //additional mark on the vertex
    QString color; //color in which vertex will be printed
    QString vertex;
};

class Edge
{
public:
    Edge(int to, int from, QString color, int label = 0);
    QString label; //additional mark on the vertex
    QString color; //color in which vertex will be printed
    QString from; //start of the edge
    QString to; //end of the edge
};

class WriteInFile
{
protected:
    int numberOfSteps = 0;
public:
    WriteInFile(const Graph& G);
    virtual ~WriteInFile() = default;
    virtual void write(void*) = 0;
    void createImage();
};

class WriteEdgeInFile :public WriteInFile
{
public:
    WriteEdgeInFile(const Graph& G): WriteInFile(G){}
    void write(void*);
};

class WriteVertexInFile :public WriteInFile
{
public:
    WriteVertexInFile(const Graph& G): WriteInFile(G){}
    void write(void*);
};

#endif // WRITEINFILE_H
