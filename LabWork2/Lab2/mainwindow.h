#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matrix.h"
#include "writeinfile.h"
#include "constants.h"
#include "GraphAlgorithms/graph_algorithm.h"
#include "graphoutput.h"

#include <QMainWindow>
#include <QRandomGenerator>
#include <QLabel>
#include <QDateTime>
#include <QDirIterator>
#include <QTimer>
#include <QMessageBox>
#include <QMovie>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const int MAXSIZE = 20; //maximum number of vertexes that is allowed

    int n = 2; //number for vertexes
    bool weighted = false; //whether graph is weighted or not
    bool directed = false; //whether graph is directed or not
    QVector<QVector<int>> graph; //matrix n*n that represent graph
    QVector<QVector<QLabel*>> labels; //labels of the printed matrix

    ////unused -- ????
    bool changeAutomatically = true; //true if images are changing on timer
    QDirIterator* it = nullptr; //pointer for iteration through Image directive


    GraphAlgorithm* algo = nullptr; //pointer on the algorithm
    int algoNumber = 0; //index of the chosen algorithm from the combo box


    /////unused --- ?????
    int numberOfSteps = -1; //number of images to illustrate certain algo work


    QLabel* graphLabel = nullptr; //label for show image ////unused-???

    QMovie *mo = nullptr;


    const QString numberOfStepsFile = QCoreApplication::applicationDirPath()+"//Files//NumberOfSteps.txt";
    const QString icon = QCoreApplication::applicationDirPath()+"//Images//icon.png";
    const QString loading = QCoreApplication::applicationDirPath()+"//Images//loading.png";
    const QString imgFolder = QCoreApplication::applicationDirPath()+"//Images//";
    const QString fileFolder = QCoreApplication::applicationDirPath()+"//Files//";
    const QString outputFile = QCoreApplication::applicationDirPath()+"//Files//output.txt";

private slots:
    /**
     * @brief print matrix in the matrix grid
     * @param matrix that should be printed
     */
    void printMatrix(QVector<QVector<int>>);

    /**
     * @brief set empty string to every label cell
     */
    void clearLabels();

    /**
     * @brief output of image sequence on the screen
     */
    //void illustrate();

    /**
     * @brief set given picture on the graphLabel
     * @param path Path of the picture
     */
   // void setPicture(QString path);

    /**
     * @brief generate the random matrix
     */
    void on_randomButton_clicked();

    /**
     * @brief sets whether the graph is directed or not
     * @param arg1 State of the check box
     */
    void on_directed_stateChanged(int arg1);

    /**
     * @brief sets whether the graph is weighted or not
     * @param arg1 State of the check box
     */
    void on_weightedGraph_stateChanged(int arg1);

    /**
     * @brief run the algorithm and generate output
     */
    void on_Run_clicked();

    /**
     * @brief creates a window where user can enter his matrix
     */
    void on_enterMatrixPushButton_clicked();

    /**
     * @brief set the number of vertexes in the graph
     *
     * @param index Chosen item in the combobox
     */
    void on_numberOfVertexes_currentIndexChanged(int index);

    /**
     * @brief show the previous state of the algorithm
     * or do nothing if current state is initial
     */
    //void on_prevPushButton_clicked();

    /**
     * @brief show the next state of the algorithm
     * or do nothing if current state is final
     */
    //void on_nextPushButton_clicked();

    /**
     * @brief choose algorithm from the comobox
     *
     * @param index Chosen item in the combobox
     */
    void on_algorithm_currentIndexChanged(int index);

    /**
     * @brief execute of the choosen algorithm,
     * generate images for its visualization
     * and show the output of the algorithm in the text area
     */
    void algoExecute();


    /**
     * @brief check if current file has to be used in the visualization
     * @param fileName Name of the file
     * @return true if file has to be used
     * false otherwise
     */
    //bool fileIsValid(QString fileName);

    /**
     * @brief read the number of steps of the current algorithm from file
     */
    //void getNumberOfSteps();

    /**
     * @brief generate image from file using graphviz
     */
    //void createImage();

    /**
     * @brief stop showing images automatically
     */
    //void on_stopPushButton_clicked();

    /**
     * @brief print the algo result on in the textArea
     */
    //void setOutput();

    /**
     * @brief set the graphLabel, resultOutput and matrix
     * to be empty
     */
    void clearOutput();

    /**
     * @brief change window size according to the number of vertexes
     */
    void setWindowSize();

};

#endif // MAINWINDOW_H
