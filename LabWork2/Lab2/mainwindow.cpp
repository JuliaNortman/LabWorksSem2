#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
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
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            QLabel *ql = new QLabel;
            ql->setFixedSize(20, 10);
            ql->setText(QString::number(matrix[i][j]));
            ui->matrixGrid->addWidget(ql, i, j);
        }
    }
}
