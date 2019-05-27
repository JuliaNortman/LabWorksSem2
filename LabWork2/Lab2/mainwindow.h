#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matrix.h"

#include <QMainWindow>

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
    int n; //number fo vertexes

private slots:
    void printMatrix(QVector<QVector<int>>); //print matrix in the matrix grid
};

#endif // MAINWINDOW_H
