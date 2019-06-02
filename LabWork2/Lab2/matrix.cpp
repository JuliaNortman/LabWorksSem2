#include "matrix.h"
#include "ui_matrix.h"

Cell::Cell()
{
    //set cell styles
    setFixedSize(35, 28);
    setValidator(new QIntValidator(-1000, 1000));
    setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                                "border-radius: 5px;}");
}

Matrix::Matrix(const int &dim, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix),
    n(dim)
{
    //set window size and style
    ui->setupUi(this);
    setFixedSize(30 + 41*n + 30, 34*n + 100);
    ui->OKPushButton->move(30+41*n-80, 34*n+100-28);
    ui->error->move(30+20*n-48, 3);

    //create the input fields
    cells.resize(n);
    for(int i = 0; i < n; ++i)
    {
        cells[i].resize(n);
        for(int j = 0; j < n; ++j)
        {
            cells[i][j] = new Cell;
            ui->matrix->addWidget(cells[i][j], i, j);
        }
    }
}

Matrix::~Matrix()
{
    //delete cells
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            delete cells[i][j];
        }
    }

    delete ui;
}

void Matrix::warning()
{
    ui->error->setText("Please, fill all cells");
}

void Matrix::on_OKPushButton_clicked()
{
    matr.resize(n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            /*if cell is empty*/
            if(cells[i][j]->text() == "")
            {
                warning(); //show warning
                return;
            }
            matr[i].resize(n);
            matr[i][j] = cells[i][j]->text().toInt();
        }
    }

    this->close();
    emit(matrix(matr));
}
