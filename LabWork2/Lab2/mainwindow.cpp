#include "mainwindow.h"
#include "ui_mainwindow.h"


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
        if(i > 1)
        {
            ui->prevPushButton->show();
            ui->nextPushButton->show();

            QString str = it->next();
            qDebug(str.toStdString().c_str());
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

void MainWindow::on_Run_clicked()
{
    QDir dir("LabWorksSem2//LabWork2//Lab2//Images");
    dir.removeRecursively();
    dir.setPath("LabWorksSem2//LabWork2//Lab2");
    dir.mkdir("Images");

    Graph g(graph, directed, weighted);
    WriteEdgeInFile f(g);
    Edge v(1, 2, "red");
    f.write(&v);

    illustrate();
}

void MainWindow::stopChanging()
{

}

bool MainWindow::stop()
{
    static bool st = false;
    return st;
}

/*void MainWindow::on_prevPushButton_clicked()
{
    changeAutomatically = false;
    int fileNumber = it->fileName().split(".")[0].toInt()-1;
    qDebug(std::to_string(fileNumber).c_str());
    if(fileNumber > 0)
    {
        QDirIterator *temp = new QDirIterator("LabWorksSem2//LabWork2//Lab2//Images//"+QString::number(fileNumber)+".png");
        it = temp;
        delete temp;
        setPicture(it->filePath());
        qDebug(it->filePath().toStdString().c_str());
    }
}*/

void MainWindow::on_nextPushButton_clicked()
{
    changeAutomatically = false;
    if(it->hasNext())
    {
        setPicture(it->next());
    }
}
