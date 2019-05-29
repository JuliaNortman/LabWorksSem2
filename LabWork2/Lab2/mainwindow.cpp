#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < 10; ++i)
    {
        QVector<QLabel*> l;
        labels[i].push_back(l);
        labels[i].resize(10);
        for(int j = 0; j < 10; ++j)
        {
            labels[j][j] = new QLabel;
        }
    }
}

MainWindow::~MainWindow()
{
    /*for(int i = 0; i < MAXSIZE; ++i)
    {
        for(int j = 0; j < MAXSIZE; ++j)
        {
            delete labels[i][j];
        }
    }*/
    delete ui;
}

void MainWindow::on_enterMatrixPushButton_clicked()
{
    Matrix* matr = new Matrix(n);
    connect(matr, SIGNAL(matrix(QVector<QVector<int>>)), this, SLOT(printMatrix(QVector<QVector<int>>)));
    matr->exec();
}


void MainWindow::on_numberOfVertexes_currentIndexChanged(int index)
{
    n = index+2;
}

void MainWindow::printMatrix(QVector<QVector<int>> matrix)
{
    graph = matrix;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            labels[i][j]->setFixedSize(20, 10);
            labels[i][j]->setText(QString::number(matrix[i][j]));
            ui->matrixGrid->addWidget(labels[i][j], i, j);
        }
    }
}

void MainWindow::on_randomButton_clicked()
{
    //allocate memory for graph
    graph.resize(n);
    for(int i = 0; i < n; ++i) graph[i].resize(n);

    for(int i = 0; i < n; ++i)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        int j = 0;

        /*if graph is undirecteed then need to generate only half of the matrix
        the rest will bw symmetric*/
        if(!directed) j = i;
        else j = 0;

        for(j; j < n; ++j)
        {
            //in order to avoid loops
            if(j == i) graph[i][j] = 0;
            else
            {
                if(weighted)
                {
                    graph[j][i] = graph[i][j] = rand()%10;
                }
                else  graph[j][i] = graph[i][j] = rand()%2;
            }
        }
    }
    printMatrix(graph);
}

void MainWindow::on_directed_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked) directed = true;
    else directed = false;
}

void MainWindow::on_weightedGraph_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked) weighted = true;
    else weighted = false;
}
