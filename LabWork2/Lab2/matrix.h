#ifndef MATRIX_H
#define MATRIX_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <QIntValidator>

class Cell : public QLineEdit
{
    Q_OBJECT

public:
    Cell();

private:
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
    void on_OKPushButton_clicked();

private:
    Ui::Matrix *ui;
    const int n; //number of vertexes in the graph
    QVector<QVector<int>> matr; //matrix n*n that represents graph
    QVector<QVector<Cell*>> cells; //QLable that allow to enter the graph matrix

    void warning();//show the warning message when not all the cells are filled

signals:
    void matrix(QVector<QVector<int>>);
};

#endif // MATRIX_H
