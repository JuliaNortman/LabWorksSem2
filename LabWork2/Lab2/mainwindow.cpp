#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <winbase.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(icon));
    setWindowTitle("GraphAlgoVisualizator");
    //qDebug(QCoreApplication::applicationDirPath().toStdString().c_str());

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

    //unused - ????
    //graphLabel = new QLabel;
    //ui->scrollGraph->setWidget(graphLabel);


    //hiding buttons
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


void MainWindow::on_numberOfVertexes_currentIndexChanged(int index)
{
    //set current number of vertexes
    n = index+2;

    //hide buttons and clear previous output
    clearOutput();
}

void MainWindow::printMatrix(QVector<QVector<int>> matrix)
{
    clearOutput();
    ui->Run->setEnabled(true);
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

    qsrand(QDateTime::currentMSecsSinceEpoch());
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
    ui->loading->show();
    Graph g(graph, directed, weighted);

    //setPicture("");
    //ui->resultTextBrowser->setText("");

    algoExecute();

    QPixmap image(loading);
    ui->loading->setPixmap(image);
    ui->loading->setScaledContents(true);


    QTime time;
    time.start();
    for(;time.elapsed() < 2000;) {
        QApplication::processEvents(nullptr);
    }
    ui->loading->hide();

    GraphOutput gOutput;
    gOutput.exec();

    //setOutput();
}


void MainWindow::algoExecute()
{
    if(algo) delete algo;

    Graph G(graph, directed, weighted);

    //choose what algo to be executed
    switch (algoNumber)
    {
    case 0:
    {
        algo = new BFS(G);
        break;
    }
    case 1:
    {
        algo = new DFS(G);
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
        algo = new ShortestPathes(G);
        break;
    }
    case 6:
    {
        algo = new MinimalSpanningTree(G);
        break;
    }
    default:
    {
        break;
    }
    }
    try
    {
        algo->executeAlgorithm();
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


    //getNumberOfSteps(); ///////unused

    //ui->visualizePushButton->setEnabled(true);

}




void MainWindow::clearOutput()
{
    ui->Run->setEnabled(false);
    //ui->prevPushButton->hide();
   // ui->nextPushButton->hide();
    //ui->stopPushButton->hide();
    //setPicture("");
    clearLabels();
   // ui->resultTextBrowser->setText("");

    QFile file(outputFile);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void MainWindow::setWindowSize()
{
    /*if(n > 5)
    {
        setFixedSize(950, 660);
        ui->stopPushButton->move(100, 80+40+250+200);
        ui->prevPushButton->move(180, 80+40+250+200);
        ui->nextPushButton->move(260, 80+40+250+200);
        //ui->graphLabel->setFixedSize(490, 450);
    }
    else
    {
        setFixedSize(750, 530);
        ui->stopPushButton->move(384, 80+40+350);
        ui->prevPushButton->move(484, 80+40+350);
        ui->nextPushButton->move(584, 80+40+350);
        ui->scrollGraph->setFixedSize(290, 250);
    }
    if(n == 2 && (graph[0][1] || graph[1][0]))
    {
        ui->scrollGraph->setFixedSize(190, 235);
    }
    else if(n == 2)
    {
        ui->scrollGraph->setFixedSize(235, 190);
    }*/
}

void MainWindow::on_algorithm_currentIndexChanged(int index)
{
    algoNumber = index;

    QFile file(outputFile);
    file.open(QIODevice::WriteOnly);
    file.close();
}
