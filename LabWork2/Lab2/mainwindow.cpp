#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <winbase.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(475, 623);
    setWindowIcon(QIcon(icon));
    setWindowTitle("GraphAlgoVisualizator");

    //initialize labels with empty strings
    for(int i = 0; i < MAXSIZE; ++i)
    {
        QVector<QLabel*> l;
        labels.push_back(l);
        for(int j = 0; j < MAXSIZE; ++j)
        {
            labels[i].push_back(new QLabel);
            labels[i][j]->setFixedSize(25, 10);
        }
    }

    clearOutput();
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < MAXSIZE; ++i)
    {
        for(int j = 0; j < MAXSIZE; ++j)
        {
            delete labels[i][j];
        }
    }
    delete ui;
}

void MainWindow::on_enterMatrixPushButton_clicked()
{
    clearOutput();
    //create window to enter users matrix
    Matrix* matr = new Matrix(n);
    connect(matr, SIGNAL(matrix(QVector<QVector<int>>)), this, SLOT(printMatrix(QVector<QVector<int>>)));
    matr->exec();
}



void MainWindow::printMatrix(QVector<QVector<int>> matrix)
{
    clearOutput();
    ui->Run->setEnabled(true);
    ui->yourMatrixLabel->show();
    graph = matrix;
    clearLabels(); //clear previous text
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            labels[i][j]->setText(QString::number(matrix[i][j]));
            ui->matrixGrid->addWidget(labels[i][j], i, j);
        }
    }
}


void MainWindow::clearLabels()
{
    //clear previous text on the labels
    for(int i = 0; i < MAXSIZE; ++i)
    {
        for(int j = 0; j < MAXSIZE; ++j) labels[i][j]->setText("");
    }
}

void MainWindow::on_randomButton_clicked()
{
    //clear output
    clearOutput();
    ui->Run->setEnabled(true);
    //allocate memory for graph
    graph.resize(n);
    for(int i = 0; i < n; ++i) graph[i].resize(n);

    qsrand(static_cast<unsigned int>(QDateTime::currentMSecsSinceEpoch()));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            //in order to avoid loops
            if(j == i) graph[i][j] = 0;
            else
            {
                if(weighted) //if weighted than generate the weight
                {
                   graph[i][j] = qrand()%10;
                }
                else graph[i][j] = qrand()%2;
            }
        }
    }
    /*if graph is undirected then need to generate only half of the matrix
    the rest will bw symmetric*/
    if(!directed)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = i; j < n; ++j) graph[i][j] = graph[j][i];
        }
    }

    //output the matrix on te screen
    printMatrix(graph);
}

void MainWindow::on_directed_stateChanged(int arg1)
{
    clearOutput();
    if(arg1 == Qt::Checked) directed = true;
    else directed = false;
}

void MainWindow::on_weightedGraph_stateChanged(int arg1)
{
    clearOutput();
    if(arg1 == Qt::Checked) weighted = true;
    else weighted = false;
}



void MainWindow::on_Run_clicked()
{
    Graph g(graph, directed, weighted);

    try
    {
        algoExecute();
        QPixmap image(loading);
        QSplashScreen splash(image);
        splash.show();

        QTime time;
        time.start();
        for(;time.elapsed() < 2000;) {
            QApplication::processEvents(nullptr);
        }
        splash.finish(this);

        GraphOutput gOutput;
        gOutput.exec();
    }
    catch (const QString str)
    {
        //call message box to show the problem
        QMessageBox::critical(nullptr, "Critical", str);
    }
    catch(...)
    {
        QString str = "Something went wrong! Please try again later";
        QMessageBox::critical(nullptr, "Critical", str);
    }
}



void MainWindow::algoExecute()
{
    if(algo) delete algo;

    Graph G(graph, directed, weighted);
    int source = ui->sourceVertex->value();

    //choose what algo to be executed
    switch (algoNumber)
    {
    case 0:
    {
        algo = new BFS(G, source);
        break;
    }
    case 1:
    {
        algo = new DFS(G, source);
        break;
    }
    case 2:
    {
        algo = new ConnectedComponents(G);
        break;
    }
    case 3:
    {
        algo = new ColorGraph(G);
        break;
    }
    case 4:
    {
        algo = new DetectCycle(G);
        break;
    }
    case 5:
    {
        algo = new ShortestPathes(G, source);
        break;
    }
    case 6:
    {
        algo = new MinimalSpanningTree(G);
        break;
    }
    case 7:
    {
        algo = new TopologicalSortingKahnAlgorithm(G);
        break;
    }
    case 8:
    {
        algo = new MaximalFlowFromSource(G, source);
        break;
    }
    default:
    {
        break;
    }
    }
   // try
    //{
        algo->executeAlgorithm();
    //}

}




void MainWindow::clearOutput()
{
    ui->Run->setEnabled(false);
    clearLabels();
    ui->yourMatrixLabel->hide();

    QFile file(outputFile);
    file.open(QIODevice::WriteOnly);
    file.close();
}


void MainWindow::on_algorithm_currentIndexChanged(int index)
{
    algoNumber = index;

    ui->sourceVertex->setEnabled(false);

    if(algoNumber == 8 || algoNumber == 5 || algoNumber == 1 || algoNumber == 0)
    {
        ui->sourceVertex->setEnabled(true);
    }

    QFile file(outputFile);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void MainWindow::on_numberOfVertexes_valueChanged(int arg1)
{
    n = arg1;
    ui->sourceVertex->setMaximum(n-1);
    clearOutput();
}

void MainWindow::on_infoPushButton_clicked()
{
    Info info;
    info.exec();
}
