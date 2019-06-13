#ifndef GRAPHOUTPUT_H
#define GRAPHOUTPUT_H

#include <QDialog>
#include <QLabel>
#include <QDirIterator>
#include <QTime>
#include <QCoreApplication>
#include <QFileDialog>
#include <windows.h>

namespace Ui {
class GraphOutput;
}

class GraphOutput : public QDialog
{
    Q_OBJECT

public:
    explicit GraphOutput(QWidget *parent = nullptr);
    ~GraphOutput();

    /**
     * @brief set image of graph
     * @param path Path to th image location
     */
    void setPicture(QString path);

    /**
     * @brief show the sequence of images
     * that show the state o the graph
     */
    void illustrate();

    /**
     * @brief check if current file has to be used in the visualization
     * @param fileName Name of the file
     * @return true if file has to be used
     * false otherwise
     */
    bool fileIsValid(QString fileName);


    /**
     * @brief read the number of steps of current algorithm execution
     * from file
     */
    void getNumberOfSteps();

    /**
     * @brief set the result of the algo execution
     * in the text area
     */
    void setOutput();

private slots:

    /**
     * @brief show previous step
     */
    void on_prevPushButton_clicked();

    /**
     * @brief show next step
     */
    void on_nextPushButton_clicked();

    /**
     * @brief stop automatic algo visualization
     */
    void on_stopPushButton_clicked();

    /**
     * @brief start algo visualization
     */
    void on_startPushButton_clicked();

    /**
     * @brief generate gif image and download it
     */
    void on_downloadGifPushButton_clicked();

private:
    Ui::GraphOutput *ui;
    QLabel* graphLabel = nullptr; //label for show images
    bool changeAutomatically = true; //true if images are changing on timer
    QDirIterator* it = nullptr; //pointer for iteration through Image directive
    int numberOfSteps = -1; //number of images to illustrate certain algo work


    const QString numberOfStepsFile = QCoreApplication::applicationDirPath()+"//Files//NumberOfSteps.txt";
    const QString imgFolder = QCoreApplication::applicationDirPath()+"//Images//";
    const QString fileFolder = QCoreApplication::applicationDirPath()+"//Files//";
    const QString outputFile = QCoreApplication::applicationDirPath()+"//Files//output.txt";
    const QString ffmpegPath = QCoreApplication::applicationDirPath()+"//Ffmpeg//bin//ffmpeg.exe";
};

#endif // GRAPHOUTPUT_H
