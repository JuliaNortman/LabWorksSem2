#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matrix.h"

#include <QMainWindow>
#include <QRandomGenerator>
#include <QLabel>
#include <ctime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_enterMatrixPushButton_clicked();

    void on_numberOfVertexes_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    const int MAXSIZE = 10;

    int n; //number for vertexes
    bool weighted = false; //whether graph is weighted or not
    bool directed = false; //whether graph is directed or not
    QVector<QVector<int>> graph; //matrix n*n that represent graph

    QVector<QVector<QLabel*>> labels; //labels of the printed matrix

private slots:
    void printMatrix(QVector<QVector<int>>); //print matrix in the matrix grid
    void on_randomButton_clicked();
    void on_directed_stateChanged(int arg1);
    void on_weightedGraph_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
