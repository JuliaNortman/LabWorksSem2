#ifndef GRAPHOUTPUT_H
#define GRAPHOUTPUT_H

#include <QDialog>
#include <QLabel>
#include <QDirIterator>
#include <QTime>
#include <QCoreApplication>

namespace Ui {
class GraphOutput;
}

class GraphOutput : public QDialog
{
    Q_OBJECT

public:
    explicit GraphOutput(QWidget *parent = nullptr);
    ~GraphOutput();

    void setPicture(QString path);
    void illustrate();
    bool fileIsValid(QString fileName);
    void getNumberOfSteps();
    void setOutput();

private slots:
    void on_prevPushButton_clicked();

    void on_nextPushButton_clicked();

    void on_stopPushButton_clicked();

    void on_startPushButton_clicked();

private:
    Ui::GraphOutput *ui;
    QLabel* graphLabel = nullptr;
    bool changeAutomatically = true; //true if images are changing on timer
    QDirIterator* it = nullptr; //pointer for iteration through Image directive
    int numberOfSteps = -1; //number of images to illustrate certain algo work


    const QString numberOfStepsFile = QCoreApplication::applicationDirPath()+"//Files//NumberOfSteps.txt";
    const QString imgFolder = QCoreApplication::applicationDirPath()+"//Images//";
    const QString fileFolder = QCoreApplication::applicationDirPath()+"//Files//";
    const QString outputFile = QCoreApplication::applicationDirPath()+"//Files//output.txt";
};

#endif // GRAPHOUTPUT_H
