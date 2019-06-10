#ifndef WRITEINFILE_H
#define WRITEINFILE_H

#include "GraphAlgorithms/graph.h"

#include <QObject>
#include <QVector>
#include <QFile>


/**
 * @brief The Vertex class
 * Used to represent the attributes of the vertex
 */
class Vertex
{
public:
    Vertex(int v, QString color, int label = 0);
    QString label; //additional mark on the vertex
    QString color; //color in which vertex will be printed
    QString vertex; //index of the vertex
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


/**
 * @brief The WriteInFile class
 * Interface class
 * has the pure virtual function write in order to write information in file
 */
class WriteInFile
{
protected:
    int numberOfSteps = 0; //number of steps in the algorithm
    Graph g; //graph
public:
    WriteInFile(const Graph& G);
    virtual ~WriteInFile() = default;
    virtual void write(void*) = 0; //pure virtual function

    /**
     * @brief generates the file name from the integer
     * that describes current number of steps
     * @return File name
     */
    const QString fileName();

    /**
     * @brief generates the file name from the integer
     * that describes number of steps
     * @return File name
     */
    const QString prevFileName();

    /**
     * @brief writes total number of steps in file
     * @param numb Total number of steps
     */
    void writeNumberOfSteps(int numb);

    void CreatePicture(const QString& path);
};


/**
 * @brief The WriteEdgeInFile class
 * writes vertex with its attribtes in the file
 */
class WriteEdgeInFile :public WriteInFile
{
public:
    WriteEdgeInFile(const Graph& G): WriteInFile(G){}
    void write(void*);
};


/**
 * @brief The WriteVertexInFile class
 * writes edge with its attribtes in the file
 */
class WriteVertexInFile :public WriteInFile
{
public:
    WriteVertexInFile(const Graph& G): WriteInFile(G){}
    void write(void*);
};

#endif // WRITEINFILE_H
