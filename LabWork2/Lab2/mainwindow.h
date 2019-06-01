#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matrix.h"
#include "writeinfile.h"
//#include "GraphAlgorithm/graph_algorithm.h"

#include <QMainWindow>
#include <QRandomGenerator>
#include <QLabel>
#include <QDateTime>
#include <QDirIterator>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

/*should be deleted
* used only for correct work of mainWindow
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const int MAXSIZE = 10;

    int n = 2; //number for vertexes
    bool weighted = false; //whether graph is weighted or not
    bool directed = false; //whether graph is directed or not
    QVector<QVector<int>> graph; //matrix n*n that represent graph
    QVector<QVector<QLabel*>> labels; //labels of the printed matrix
    bool changeAutomatically = true; //true if images are changing on timer
    QDirIterator* it = nullptr;
    GraphAlgorithm* algo = nullptr; //pointer on the algorithm
    int algoNumber = 0;

private slots:
    void printMatrix(QVector<QVector<int>>); //print matrix in the matrix grid
    void clearLabels(); //set empty string to every cell
    void illustrate();
    void setPicture(QString path);

    void on_randomButton_clicked();  
    void on_directed_stateChanged(int arg1);
    void on_weightedGraph_stateChanged(int arg1);
    void on_Run_clicked();
    void on_enterMatrixPushButton_clicked();

    void on_numberOfVertexes_currentIndexChanged(int index);
    void stopChanging(); //is called after prev or next button is clicked in order to stop automatic changes of the pictures
    bool stop();
    //void on_prevPushButton_clicked();
    void on_nextPushButton_clicked();
    void on_algorithm_currentIndexChanged(int index);
    void algoExecute();
    void removeFilesInDir(const QString& dirName);
};

#endif // MAINWINDOW_H
