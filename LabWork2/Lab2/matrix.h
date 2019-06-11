#ifndef MATRIX_H
#define MATRIX_H

#include "constants.h"

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <QIntValidator>


/**
 * @brief The Cell class that represents cell in the matrix output
 */
class Cell : public QLineEdit
{
    Q_OBJECT

public:
    Cell();
};

namespace Ui {
class Matrix;
}



class Matrix : public QDialog
{
    Q_OBJECT

public:
    explicit Matrix(const int &dim, QWidget *parent = nullptr);
    ~Matrix();

private slots:

    /**
     * @brief checks if the input is valid
     * and emits signal matrix()
     */
    void on_OKPushButton_clicked();

private:
    Ui::Matrix *ui;
    const int n; //number of vertexes in the graph
    QVector<QVector<int>> matr; //matrix n*n that represents graph
    QVector<QVector<Cell*>> cells; //QLable that allow to enter the graph matrix

    /**
     * @brief show the warning message when not all the cells are filled
     */
    void warning();

signals:
    /**
     * @brief emits in order to pass the matrix to the mainwindow
     */
    void matrix(QVector<QVector<int>>);
};

#endif // MATRIX_H
