#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <gtest/gtest.h>
#include <iostream>
#include <QApplication>
#include <QFile>

#include "graph.h"
#include "graph_algorithm.h"

/**
* Must be the same ass GraphAlgorithm::pathToFile,
* and relate to directory of building the main project.
*/
const QString PATH_TO_FILE = "C:\\QTProjectsMy\\gAlgo\\output.txt";

TEST(Graph, constructorGraphFuncTest)
{
    QVector<QVector<int>> m1 = {{0,1,1},{1,0,0},{1,0,0}};
    QVector<QVector<int>> m2 = {{0,0,0},{1,0,1},{0,0,0}};
    QVector<QVector<int>> m3 = {{0,4,0},{0,0,0},{0,8,0}};
    QVector<QVector<int>> m4 = {{0,0,3},{0,0,7},{3,7,0}};

    bool w1 = false ;
    bool or1 = false;
    bool w2 = false;
    bool or2 = true;
    bool w3 = true;
    bool or3 = true;
    bool w4 = true;
    bool or4 = false;

    Graph *g1 = new Graph(m1,or1, w1);
    Graph *g2 = new Graph (m2,or2, w2);
    Graph *g3 = new Graph(m3,or3, w3);
    Graph *g4 = new Graph(m4,or4, w4);

    EXPECT_EQ(g1->oriented, or1);
    EXPECT_EQ(g2->oriented, or2);
    EXPECT_EQ(g3->oriented, or3);
    EXPECT_EQ(g4->oriented, or4);

    EXPECT_EQ(g1->weighted, w1);
    EXPECT_EQ(g2->weighted, w2);
    EXPECT_EQ(g3->weighted, w3);
    EXPECT_EQ(g4->weighted, w4);

    const int sizeAllGrpahsInTest = 3;
    for (int i=0; i<sizeAllGrpahsInTest ; i++)
    {
        for (int j=0; j<sizeAllGrpahsInTest; j++)
        {
            EXPECT_EQ(g1->graph[i][j], m1[i][j]);
            EXPECT_EQ(g2->graph[i][j], m2[i][j]);
            EXPECT_EQ(g3->graph[i][j], m3[i][j]);
            EXPECT_EQ(g4->graph[i][j], m4[i][j]);
        }
    }
}

TEST(Graph, hasCycleFuncTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                    {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}};
    QVector<QVector<int>> correctUndirectedUnweightedCyclickG = {{0,1,0,0,0,0},{1,0,1,1,0,0},{0,1,0,0,0,0},
                                                                 {0,1,0,0,1,1},{0,0,0,1,0,1},{0,0,0,1,1,0}};
    QVector<QVector<int>> correctUnirectedUnweightedCyclicG3 = {{0,1,1},{1,0,1},{1,1,0}};
    QVector<QVector<int>> correctDirectedUnweightedCyclicG2 = {{0,1,0},{0,0,1},{1,0,0}};
    Graph *gc1 = new Graph (correctUndirectedUnweightedCyclickG, false, false);
    Graph *gc3 = new Graph(correctUnirectedUnweightedCyclicG3,false, false);
    Graph *gnc1 = new Graph (correctUndirectedUnweightedNotCyclickG, false, false);
    Graph *gc2 = new Graph(correctDirectedUnweightedCyclicG2,true, false);

    EXPECT_TRUE(gc1->hasCycle());
    EXPECT_TRUE(gc3->hasCycle());
    EXPECT_FALSE(gnc1->hasCycle());
    EXPECT_TRUE(gc2->hasCycle());

}

TEST(Graph, hasNegativeWeightEdgeFuncTest)
{
    QVector<QVector<int>> correctUnirectedUnweightedCyclicG3 = {{0,1,1},{1,0,1},{1,0,0}};
    QVector<QVector<int>> correctUndirectedWeightedCyclic = {{0,3,-7},{3,0,4},{-7,4,0}};

    Graph *g = new Graph(correctUnirectedUnweightedCyclicG3, false, false);
    Graph *gNeg = new Graph(correctUndirectedWeightedCyclic, false, false);
    EXPECT_TRUE(gNeg->hasNegativeWeightEdge());
    EXPECT_FALSE(g->hasNegativeWeightEdge());
}


TEST(Graph, BFSfromFuncTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                    {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}}; //1
    QVector<QVector<int>> correctUndirectedUnweightedCyclickG = {{0,1,0,0,0,0},{1,0,1,1,0,0},{0,1,0,0,0,0},
                                                                 {0,1,0,0,1,1},{0,0,0,1,0,1},{0,0,0,1,1,0}}; //2

    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    QVector<int> gv1, gv2, gv3;
    Graph *g1 = new Graph(correctUndirectedUnweightedNotCyclickG, false, false);
    Graph *g2 = new Graph(correctUndirectedUnweightedCyclickG, false, false);
    Graph *g3 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);

    gv1 = g1->BFSfrom(); //expected 012534
    gv2 = g2->BFSfrom(3); //expected 314502
    gv3 = g3->BFSfrom(1); //expected 1032

    EXPECT_TRUE(gv1.size() == g1->graph.size());
    EXPECT_TRUE(gv2.size() == g2->graph.size());
    EXPECT_TRUE(gv3.size() == g3->graph.size());

    EXPECT_EQ(gv1[0], 0);
    EXPECT_EQ(gv1[1], 1);
    EXPECT_EQ(gv1[2], 2);
    EXPECT_EQ(gv1[3], 5);
    EXPECT_EQ(gv1[4], 3);
    EXPECT_EQ(gv1[5], 4);

    EXPECT_EQ(gv2[0], 3);
    EXPECT_EQ(gv2[1], 1);
    EXPECT_EQ(gv2[2], 4);
    EXPECT_EQ(gv2[3], 5);
    EXPECT_EQ(gv2[4], 0);
    EXPECT_EQ(gv2[5], 2);

    EXPECT_EQ(gv3[0], 1);
    EXPECT_EQ(gv3[1], 0);
    EXPECT_EQ(gv3[2], 3);
    EXPECT_EQ(gv3[3], 2);
}


TEST(Graph, DFSfromFuncTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                    {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}}; //1
    QVector<QVector<int>> correctUndirectedUnweightedCyclickG = {{0,1,0,0,0,0},{1,0,1,1,0,0},{0,1,0,0,0,0},
                                                                 {0,1,0,0,1,1},{0,0,0,1,0,1},{0,0,0,1,1,0}}; //2

    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    QVector<int> gv1, gv2, gv3;
    Graph *g1 = new Graph(correctUndirectedUnweightedNotCyclickG, false, false);
    Graph *g2 = new Graph(correctUndirectedUnweightedCyclickG, false, false);
    Graph *g3 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);

    gv1 = g1->DFSfrom(); //expected 052143
    gv2 = g2->DFSfrom(3); //expected 354120
    gv3 = g3->DFSfrom(1); //expected 1302

    EXPECT_TRUE(gv1.size() == g1->graph.size());
    EXPECT_TRUE(gv2.size() == g2->graph.size());
    EXPECT_TRUE(gv3.size() == g3->graph.size());

    EXPECT_EQ(gv1[0], 0);
    EXPECT_EQ(gv1[1], 5);
    EXPECT_EQ(gv1[2], 2);
    EXPECT_EQ(gv1[3], 1);
    EXPECT_EQ(gv1[4], 4);
    EXPECT_EQ(gv1[5], 3);

    EXPECT_EQ(gv2[0], 3);
    EXPECT_EQ(gv2[1], 5);
    EXPECT_EQ(gv2[2], 4);
    EXPECT_EQ(gv2[3], 1);
    EXPECT_EQ(gv2[4], 2);
    EXPECT_EQ(gv2[5], 0);

    EXPECT_EQ(gv3[0], 1);
    EXPECT_EQ(gv3[1], 3);
    EXPECT_EQ(gv3[2], 0);
    EXPECT_EQ(gv3[3], 2);
}

TEST(Graph, isConnectedFuncTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                    {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}}; //1
    QVector<QVector<int>> correctUndirectedUnweightedCyclickG = {{0,1,0,0,0,0},{1,0,1,1,0,0},{0,1,0,0,0,0},
                                                                 {0,1,0,0,1,1},{0,0,0,1,0,1},{0,0,0,1,1,0}}; //2

    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    QVector<QVector<int>> correctDirectedUnweightCyclicG4 = {{0,0,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,0}}; //4
    Graph *g1 = new Graph(correctUndirectedUnweightedNotCyclickG, false, false);
    Graph *g2 = new Graph(correctUndirectedUnweightedCyclickG, false, false);
    Graph *g3 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);
    Graph *g4 = new Graph(correctDirectedUnweightCyclicG4, true, false);

    EXPECT_TRUE(g1->isConnected());
    EXPECT_TRUE(g2->isConnected());
    EXPECT_FALSE(g3->isConnected());
    EXPECT_TRUE(g4->isConnected());
}


/**
* Tests to be declared as FRIEND_TESTs in corresponding classes.
* Needs google test to be included in main project file with pathes included and files attached.
*/

TEST(Graph, hasLoopsFuncTest)
{

    QVector<QVector<int>> correctUnirectedUnweightedCyclicG3 = {{0,1,1},{1,0,1},{1,0,0}};
    QVector<QVector<int>> correctDirectedUnweightedCyclicG2 = {{0,1,0},{0,0,1},{1,0,0}};
    QVector<QVector<int>> incorrectGraph = {{1,1,1},{1,1,1},{1,0,1}};

    Graph *g1 = new Graph(correctUnirectedUnweightedCyclicG3, false, false);
    Graph *g2 = new Graph(correctDirectedUnweightedCyclicG2, true, false);
    Graph *g3 = new Graph(incorrectGraph, true, false);

    EXPECT_FALSE(g1->hasLoops());
    EXPECT_FALSE(g2->hasLoops());

    for (int i=0; i<g3->graph.size(); i++){g3->graph[i][i] = 1;}
    EXPECT_TRUE(g3->hasLoops());
}


TEST(Graph, isCorrectGraphFuncTest)
{
    QVector<QVector<int>> correctUnirectedUnweightedCyclicG3 = {{0,1,1},{1,0,1},{1,1,0}};
    QVector<QVector<int>> correctDirectedUnweightedCyclicG2 = {{0,1,0},{0,0,1},{1,0,0}};
    QVector<QVector<int>> incorrectGraph = {{1,1,1},{1,1,1},{1,0,1}};

    Graph *g1 = new Graph(correctUnirectedUnweightedCyclicG3, false, false);
    Graph *g2 = new Graph(correctDirectedUnweightedCyclicG2, true, false);
    Graph *g3 = new Graph(incorrectGraph, true, false);

    EXPECT_TRUE(g1->isCorrectGraph());
    EXPECT_TRUE(g2->isCorrectGraph());

    for (int i=0; i<g3->graph.size(); i++){g3->graph[i][i] = 1;}
    EXPECT_FALSE(g3->isCorrectGraph());
}

TEST(Graph, hasSymmetricMatrixFuncTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                    {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}}; //1
    QVector<QVector<int>> correctUndirectedUnweightedCyclickG = {{0,1,0,0,0,0},{1,0,1,1,0,0},{0,1,0,0,0,0},
                                                                 {0,1,0,0,1,1},{0,0,0,1,0,1},{0,0,0,1,1,0}}; //2
    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    QVector<QVector<int>> correctDirectedUnweightCyclicG4 = {{0,0,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,0}}; //4

    Graph *g1 = new Graph(correctUndirectedUnweightedNotCyclickG, false, false);
    Graph *g2 = new Graph(correctUndirectedUnweightedCyclickG, false, false);
    Graph *g3 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);
    Graph *g4 = new Graph(correctDirectedUnweightCyclicG4, true, false);

    EXPECT_TRUE(g1->hasSymmectricMatrix());
    EXPECT_TRUE(g2->hasSymmectricMatrix());
    EXPECT_FALSE(g3->hasSymmectricMatrix());
    EXPECT_FALSE(g4->hasSymmectricMatrix());

}

TEST(Graph, hasSquareMatrixFuncTest)
{
    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    QVector<QVector<int>> correctDirectedUnweightCyclicG4 = {{0,0,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,0}}; //4
    QVector<QVector<int>> ramdomIncorrectG1 = {{0,1,1,1},{0,1,1},{0,1}};
    QVector<QVector<int>> ramdomIncorrectG2 = {{0,0,1},{1,1},{1,1,1,1,0,0}};

    Graph *g3 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);
    Graph *g4 = new Graph(correctDirectedUnweightCyclicG4, true, false);
    Graph *g1 = new Graph(ramdomIncorrectG1, true, false);
    Graph *g2 = new Graph(ramdomIncorrectG2, true, false);

    EXPECT_TRUE(g3->hasSquareMatrix());
    EXPECT_TRUE(g4->hasSquareMatrix());
    EXPECT_FALSE(g1->hasSquareMatrix());
    EXPECT_FALSE(g2->hasSquareMatrix());

}

TEST(Graph, delteLoopsFuncTest)
{
    QVector<QVector<int>> incorrectGraph = {{1,1,1},{1,1,1},{1,0,1}};
    Graph *g = new Graph(incorrectGraph, true, true);
    g->deleteLoops();
    for (int i=0; i<g->graph.size(); i++)
    {
        EXPECT_EQ(g->graph[i][i], 0);
    }
}

TEST(Graph, transponseFuncTest)
{
    QVector<QVector<int>> correctDirectedUnweightCyclicG4 = {{0,0,1,0},
                                                             {1,0,0,1},
                                                             {0,1,0,0},
                                                             {0,0,1,0}}; //4
    Graph *g = new Graph(correctDirectedUnweightCyclicG4, true, false);
    g->transponse();
    EXPECT_EQ(g->graph[0][0],0); EXPECT_EQ(g->graph[0][1],1); EXPECT_EQ(g->graph[0][2],0); EXPECT_EQ(g->graph[0][3],0);
    EXPECT_EQ(g->graph[1][0],0); EXPECT_EQ(g->graph[1][1],0); EXPECT_EQ(g->graph[1][2],1); EXPECT_EQ(g->graph[1][3],0);
    EXPECT_EQ(g->graph[2][0],1); EXPECT_EQ(g->graph[2][1],0); EXPECT_EQ(g->graph[2][2],0); EXPECT_EQ(g->graph[2][3],1);
    EXPECT_EQ(g->graph[3][0],0);EXPECT_EQ(g->graph[3][1],1);EXPECT_EQ(g->graph[3][2],0);EXPECT_EQ(g->graph[3][3],0);

    //the same check using cycles
    for (int i=0; i<correctDirectedUnweightCyclicG4.size(); i++)
        for (int j=0; j<correctDirectedUnweightCyclicG4.size(); j++)
            EXPECT_EQ(g->graph[i][j], correctDirectedUnweightCyclicG4[j][i]);
}


TEST(Graph, correctGraphFuncTest)
{
    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    QVector<QVector<int>> correctDirectedUnweightCyclicG4 = {{0,0,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,0}}; //4
    QVector<QVector<int>> ramdomIncorrectG1 = {{0,1,1},{0,1,1,1},{0,1}};

    Graph *g3 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);
    Graph *g4 = new Graph(correctDirectedUnweightCyclicG4, true, false);
    Graph *g1 = new Graph(ramdomIncorrectG1, true, false);

    g1->correctGraph();
    g3->correctGraph();
    g4->correctGraph();

    EXPECT_TRUE(g1->isCorrectGraph());
    EXPECT_TRUE(g3->isCorrectGraph());
    EXPECT_TRUE(g4->isCorrectGraph());
}

TEST(GraphAlgorithm, BFSTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                        {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}}; //1
    Graph *g1 = new Graph(correctUndirectedUnweightedNotCyclickG, false, false);
    BFS *bfs = new BFS(*g1);
    bfs->executeAlgorithm();

    QFile file1(PATH_TO_FILE);
    file1.open(QIODevice::ReadOnly);
    QString result = "";
    while(!file1.atEnd())
    {
        result += file1.readLine();
    }
    QString expect = "0 1 2 5 3 4 "; //012534
    file1.close();

    EXPECT_TRUE(result == expect);

    //test case2
    QVector<QVector<int>> correctDirectedUnweightNotCyclicG3 = {{0,0,1,0},{1,0,0,1},{0,0,0,0},{0,0,0,0}}; //3
    Graph *g2 = new Graph(correctDirectedUnweightNotCyclicG3, true, false);
    BFS *bfs2 = new BFS(*g2);
    bfs2->executeAlgorithm();

    QFile file2(PATH_TO_FILE);
    file2.open(QIODevice::ReadOnly);
    QString result2 = "";
    while(!file2.atEnd())
    {
        result2 += file2.readLine();
    }
    QString expect2 = "0 2 "; //expected 1032
    file2.close();

    EXPECT_TRUE(result2 == expect2);

}

TEST(GraphAlgorithm, DFSTest)
{
    QVector<QVector<int>> correctUndirectedUnweightedNotCyclickG = {{0,1,1,0,0,1},{1,0,0,1,1,0},{1,0,0,0,0,0},
                                                                        {0,1,0,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0}}; //1
    Graph *g1 = new Graph(correctUndirectedUnweightedNotCyclickG, false, false);
    DFS *dfs = new DFS(*g1);
    dfs->executeAlgorithm();

    QFile file1(PATH_TO_FILE);
    file1.open(QIODevice::ReadOnly);
    QString result = "";
    while(!file1.atEnd())
    {
        result += file1.readLine();
    }
    QString expect = "0 5 2 1 4 3 "; //expected 052143
    file1.close();

    EXPECT_TRUE(result == expect);

    //test case2
    QVector<QVector<int>> mg2 = {{0,0,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,0}};
    Graph *g2 = new Graph(mg2, true, false);
    DFS *dfs2 =  new DFS(*g2);
    dfs2->executeAlgorithm();

    QFile file2(PATH_TO_FILE);
    file2.open(QIODevice::ReadOnly);
    QString result2 = "";
    while(!file2.atEnd())
    {
        result2 += file2.readLine();
    }
    QString expect2 = "0 2 1 3 "; //expected 0213
    file2.close();

    EXPECT_TRUE(result2 == expect2);
}

TEST(GraphAlgorithm, ConnectedComponentsTest)
{
    //test case 1
    QVector<QVector<int>> mg1 = {{0,0,0},{0,0,0},{0,0,0}};
    Graph *g1 = new Graph(mg1, false, false);
    ConnectedComponents *cc1 =  new ConnectedComponents(*g1);
    cc1->executeAlgorithm();

    QFile file1(PATH_TO_FILE);
    file1.open(QIODevice::ReadOnly);
    QString result1 = "";
    while(!file1.atEnd())
    {
        result1 += file1.readLine();
    }
    QString expect1 = "0 1 | 2 "; //expected value
    file1.close();

    EXPECT_TRUE(result1 == expect1);

    //test case 2
    QVector<QVector<int>> mg2 = {{0,0,1,0},{1,0,0,1},{0,1,0,0},{0,0,1,0}};
    Graph *g2 = new Graph(mg2, true, false);
    ConnectedComponents *cc2 =  new ConnectedComponents(*g2);
    cc2->executeAlgorithm();

    QFile file2(PATH_TO_FILE);
    file2.open(QIODevice::ReadOnly);
    QString result2 = "";
    while(!file2.atEnd())
    {
        result2 += file2.readLine();
    }

    QString expect2 = "0 2 1 3 "; //expected value
    file2.close();

    EXPECT_TRUE(result2 == expect2);
}

TEST(GraphAlgorithm, ColorGraphTest)
{

}

TEST(GraphAlgorithm, DetectCycleTest)
{

}

TEST(GraphAlgorithm, ShortestPathesTest)
{

}

TEST(GraphAlgorithm, MinimalSpanningTreeTest)
{
    QVector<QVector<int>> a = {{0,10,2,0,20,0},{10,0,5,3,0,0},{2,5,0,0,1,0},{0,3,0,0,40,0},{20,0,1,40,0,10},{0,0,0,0,10,0}};
    Graph *g = new Graph(a, false, true);
    MinimalSpanningTree * t = new MinimalSpanningTree(*g);
    t->executeAlgorithm();

    QFile file1(PATH_TO_FILE);
    file1.open(QIODevice::ReadOnly);
    QString result1 = "";
    while(!file1.atEnd())
    {
        result1 += file1.readLine();
    }
    QString expect1 = "2--4 \n0--2 \n1--3 \n2--1 \n 4--5 \n"; //expected value
    file1.close();

    EXPECT_TRUE(result1 == expect1);
}


#endif // MAIN_H
