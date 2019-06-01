#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <winbase.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initialize labels with empty strings
    for(int i = 0; i < MAXSIZE; ++i)
    {
        QVector<QLabel*> l;
        labels.push_back(l);
        for(int j = 0; j < MAXSIZE; ++j)
        {
            labels[i].push_back(new QLabel);
            labels[i][j]->setFixedSize(20, 10);
        }
    }

    //hiding buttons
    ui->prevPushButton->hide();
    ui->nextPushButton->hide();
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
    for(int i = 0; i < MAXSIZE; ++i)
    {
        for(int j = 0; j < MAXSIZE; ++j) labels[i][j]->setText("");
    }
}

void MainWindow::on_randomButton_clicked()
{
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
                if(weighted)
                {
                   graph[i][j] = qrand()%10;
                }
                else graph[i][j] = qrand()%2;
            }
        }
    }
    /*if graph is undirecteed then need to generate only half of the matrix
    the rest will bw symmetric*/
    if(!directed)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = i; j < n; ++j) graph[i][j] = graph[j][i];
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

void MainWindow::illustrate()
{
    if(it) delete it;
    it = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Images", QDirIterator::NoIteratorFlags);

    int i = 0;
    while (it->hasNext() && changeAutomatically)
    {
        QString str = it->next();
        if(i > 1)
        {
            ui->prevPushButton->show();
            ui->nextPushButton->show();


            //qDebug(str.toStdString().c_str());
            setPicture(str);
            QTime time;
            time.start();
            for(;time.elapsed() < 800;) {
                QApplication::processEvents(nullptr);
            }
        }
        ++i;
    }
}

void MainWindow::setPicture(QString path)
{
    QPixmap image(path);
    ui->graphLabel->setPixmap(image);
    ui->graphLabel->setScaledContents(true);
}

void MainWindow::clearDir(const QString& dirName)
{
    QDir dir("LabWorksSem2//LabWork2//Lab2//"+dirName);
    dir.removeRecursively();
    dir.setPath("LabWorksSem2//LabWork2//Lab2");
    int i = 0;
    while(!dir.mkdir(dirName))
    {
        qDebug(std::to_string(++i).c_str());
    }
}

void MainWindow::on_Run_clicked()
{
    clearDir("Files");

    Graph g(graph, directed, weighted);
    WriteVertexInFile f(g);
    for(int i = 0; i < n; ++i)
    {
        Vertex v(i+1, "red");
        f.write(&v);
    }



    algoExecute();
    //illustrate();
}

bool MainWindow::stop()
{
    static bool st = false;
    return st;
}

void MainWindow::on_prevPushButton_clicked()
{
    changeAutomatically = false;
    int fileNumber = it->fileName().split(".")[0].toInt() - 1;
    QString filePath = "";
    if(fileNumber > 9) filePath = QString::number(fileNumber)+".png";
    else filePath = "0" + QString::number(fileNumber)+".png";
    QString path = "LabWorksSem2//LabWork2//Lab2//Images//"+filePath;
    if(fileNumber > 0)
    {
        setPicture(path);
    }
    else return;
    delete it;
    it = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Images//", QDirIterator::NoIteratorFlags);
    while(path != it->filePath() && it->hasNext())
    {
        it->next();
    }
}

void MainWindow::on_nextPushButton_clicked()
{
    changeAutomatically = false;
    if(it->hasNext())
    {
        setPicture(it->next());
    }
}

void MainWindow::on_algorithm_currentIndexChanged(int index)
{
    algoNumber = index;
}

void MainWindow::algoExecute()
{
    if(algo) delete algo;
    Graph G(graph, directed, weighted);
    switch (algoNumber)
    {
    case 0:
    {
        //algo = new BFS(G);
        qDebug("BFS");
        break;
    }
    case 1:
    {
        //algo = new DFS(G);
        qDebug("DFS");
        break;
    }
    case 2:
    {
        //algo = new ConnectedComponents(G);
        qDebug("ConnectedComponents ");
        break;
    }
    case 3:
    {
        //algo = new ColorGraph(G);
        qDebug("ColorGraph");
        break;
    }
    case 4:
    {
        //algo = new DetectCycle(G);
        qDebug("DetectCycle");
        break;
    }
    case 5:
    {
        //algo = new ShortestPathes(G);
        qDebug("ShortestPathes");
        break;
    }
    case 6:
    {
        //algo = new MinimalSpanningTree(G);
        qDebug("MinimalSpanningTree");
        break;
    }
    default:
    {
        break;
    }
    }
    /*try
    {
        algo->executeAlgorithm();
    }
    catch (const QString& str)
    {
        //call message box to show the problem
        QMessageBox::critical(nullptr, "Critical", str);
    }
    catch(...)
    {
        QString str = "Something went wrong! Please try again later";
        QMessageBox::critical(nullptr, "Critical", str);
    }*/

    clearDir("Images");

    QDirIterator *itFiles = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Files", QDirIterator::NoIteratorFlags);

    int i = 0;
    int numberOfSteps = 1;
    while (itFiles->hasNext())
    {
        QString str = itFiles->next();
        if(i > 1)
        {
            QString imageName = "";
            if(numberOfSteps > 9) imageName = QString::number(numberOfSteps)+".png";
            else imageName = "0"+QString::number(numberOfSteps)+".png";
            QString pp = "C:\\Users\\HP250\\Documents\\2semester\\Proga\\LABS\\";
            QString graphvizPath = "labworkssem2\\labwork2\\lab2\\graphviz\\release\\bin\\dot.exe";
            QString filePath = itFiles->filePath(); //"labworkssem2\\labwork2\\lab2\\files\\graphviz.dat";
            QString imagePath = "labworkssem2\\labwork2\\lab2\\Images\\"+imageName;
            QString myPath = graphvizPath+" -Tpng "+filePath+ " -o " + imagePath;

            /*STARTUPINFOW si;
            PROCESS_INFORMATION pi;

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            if (CreateProcessW(myPath.toStdWString().c_str(), nullptr, nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
            {
                qDebug("create process");
                WaitForSingleObject(pi.hProcess, INFINITE);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
            system(myPath.toStdString().c_str());*/

            if(WinExec(myPath.toStdString().c_str(), SW_HIDE) > 31)
            {
                qDebug("picture was generated");
            }

            numberOfSteps++;
        }
        ++i;
    }
    //illustrate();
}

void MainWindow::on_visualizePushButton_clicked()
{
    illustrate();
}
