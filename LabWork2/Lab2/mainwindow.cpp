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
            labels[i][j]->setFixedSize(25, 10);
        }
    }

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

void MainWindow::setPicture(QString path)
{
    QPixmap image(path);
    ui->graphLabel->setPixmap(image);
    ui->graphLabel->setScaledContents(true);
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

void MainWindow::illustrate()
{
    if(it) delete it; //delete previuos iterator
    it = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Images", QDirIterator::NoIteratorFlags);//set iterator
    changeAutomatically = true; //in order to cahnge pictures on timer
    int i = 0;
    while (it->hasNext() && changeAutomatically)
    {
        QString str = it->next();
        if(i > 1)
        {
            ui->stopPushButton->show();
            ui->prevPushButton->show();
            ui->nextPushButton->show();

            if(!fileIsValid(it->fileName())) break;
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

bool MainWindow::fileIsValid(QString fileName)
{
    bool converted = false;
    /*
      * Get the file name without its expansion
      * Convert the file name into the step
      * Check if the step is less or equal then the maximum number of steps
      * in the algorithm
    */
    int name = fileName.split(".")[0].toInt(&converted);
    if(!converted) return false;
    if(name <= numberOfSteps) return true;
    return false;
}

void MainWindow::getNumberOfSteps()
{
    QFile numbofsteps("LabWorksSem2//LabWork2//Lab2//Files//NumberOfSteps.txt");
    if(!numbofsteps.open(QIODevice::ReadOnly)) //open file
    {
        qDebug("Not open");
        return;
    }
    numberOfSteps = numbofsteps.readLine().toInt();//read number of steps from the file
    numbofsteps.close();
}

void MainWindow::on_Run_clicked()
{
    Graph g(graph, directed, weighted);

    setPicture("");
    ui->resultTextBrowser->setText("");

    algoExecute();
    setOutput();
}


void MainWindow::on_prevPushButton_clicked()
{
    changeAutomatically = false;
    ui->stopPushButton->setEnabled(false);

    //find the previous step
    int fileNumber = it->fileName().split(".")[0].toInt() - 1;
    if(fileNumber > numberOfSteps) fileNumber = numberOfSteps-1;
    QString filePath = "";
    if(fileNumber > 9) filePath = QString::number(fileNumber)+".png";
    else filePath = "0" + QString::number(fileNumber)+".png";
    QString path = "LabWorksSem2//LabWork2//Lab2//Images//"+filePath;
    if(fileNumber > 0)
    {
        setPicture(path);
    }
    else return;
    if(it) delete it;

    //set the current iterator to be the previous step
    it = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Images//", QDirIterator::NoIteratorFlags);
    while(path != it->filePath() && it->hasNext())
    {
        it->next();
    }
}

void MainWindow::on_nextPushButton_clicked()
{
    //check if the file is valid then show it
    changeAutomatically = false;
    ui->stopPushButton->setEnabled(false);

    if(it->hasNext())
    {
        QString filePath = it->next();
        QString filePath1 = it->fileName();
        qDebug(filePath1.toStdString().c_str());
        if(!fileIsValid(it->fileName())) return;
        setPicture(filePath);
    }
}

void MainWindow::on_algorithm_currentIndexChanged(int index)
{
    algoNumber = index;
    //clear output but keep the matrix
    ui->stopPushButton->hide();
    ui->prevPushButton->hide();
    ui->nextPushButton->hide();
    setPicture("");
    ui->resultTextBrowser->setText("");
    ui->visualizePushButton->setEnabled(false);
    QFile file("LabWorksSem2//LabWork2//Lab2//Files//output.txt");
    file.open(QIODevice::WriteOnly);
    file.close();
}

void MainWindow::createImage()
{
    QDirIterator *itFiles = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Files", QDirIterator::NoIteratorFlags);

    int i = 0;
    int localNumberOfSteps = 1;
    while (itFiles->hasNext())
    {
        QString str = itFiles->next();
        if(i > 1)
        {
            QString imageName = "";
            if(localNumberOfSteps > 9) imageName = QString::number(localNumberOfSteps)+".png";
            else imageName = "0"+QString::number(localNumberOfSteps)+".png";
            if(!fileIsValid(imageName)) break;
            QString graphvizPath = "labworkssem2\\labwork2\\lab2\\graphviz\\release\\bin\\dot.exe";
            QString filePath = itFiles->filePath(); //"labworkssem2\\labwork2\\lab2\\files\\graphviz.dat";
            QString imagePath = "labworkssem2\\labwork2\\lab2\\Images\\"+imageName;
            QString myPath = graphvizPath+" -Tpng "+filePath+ " -o " + imagePath;

            //lauch graphviz to generate a picture
            WinExec(myPath.toStdString().c_str(), SW_HIDE);

            localNumberOfSteps++;
        }
        ++i;
    }
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


    getNumberOfSteps();

    createImage();

    ui->visualizePushButton->setEnabled(true);
}

void MainWindow::on_visualizePushButton_clicked()
{
    setWindowSize();
    ui->stopPushButton->setEnabled(true);
    illustrate();
}

void MainWindow::on_stopPushButton_clicked()
{
    changeAutomatically = false;
    ui->stopPushButton->setEnabled(false);
}

void MainWindow::setOutput()
{
    QFile output("LabWorksSem2//LabWork2//Lab2//Files//output.txt");

    if(!output.open(QIODevice::ReadOnly)) //open file
    {
        qDebug("Not open");
        return;
    }


    ui->resultTextBrowser->setText("");
    while(!output.atEnd())
    {
        QString line = output.readLine();
        ui->resultTextBrowser->append(line);
    }
}

void MainWindow::clearOutput()
{
    ui->Run->setEnabled(false);
    ui->visualizePushButton->setEnabled(false);
    ui->prevPushButton->hide();
    ui->nextPushButton->hide();
    ui->stopPushButton->hide();
    setPicture("");
    clearLabels();
    ui->resultTextBrowser->setText("");

    QFile file("LabWorksSem2//LabWork2//Lab2//Files//output.txt");
    file.open(QIODevice::WriteOnly);
    file.close();
}

void MainWindow::setWindowSize()
{
    if(n > 5)
    {
        setFixedSize(950, 660);
        ui->stopPushButton->move(100, 80+40+250+200);
        ui->prevPushButton->move(180, 80+40+250+200);
        ui->nextPushButton->move(260, 80+40+250+200);
        ui->graphLabel->setFixedSize(490, 450);
    }
    else
    {
        setFixedSize(750, 530);
        ui->stopPushButton->move(384, 80+40+350);
        ui->prevPushButton->move(484, 80+40+350);
        ui->nextPushButton->move(584, 80+40+350);
        ui->graphLabel->setFixedSize(290, 250);
    }
    if(n == 2 && (graph[0][1] || graph[1][0]))
    {
        ui->graphLabel->setFixedSize(190, 235);
    }
    else if(n == 2)
    {
        ui->graphLabel->setFixedSize(235, 190);
    }
}
