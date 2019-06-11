#include "graphoutput.h"
#include "ui_graphoutput.h"

GraphOutput::GraphOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphOutput)
{
    ui->setupUi(this);

    graphLabel = new QLabel;
    ui->scrollGraph->setWidget(graphLabel);

    getNumberOfSteps();

    setOutput();
    ui->stopPushButton->hide();
    ui->prevPushButton->hide();
    ui->nextPushButton->hide();
    //illustrate();
}

GraphOutput::~GraphOutput()
{
    delete ui;
}


void GraphOutput::setPicture(QString path)
{
    QPixmap image(path);
    graphLabel->setPixmap(image);
}

void GraphOutput::illustrate()
{
    if(it) delete it; //delete previuos iterator
    it = new QDirIterator(imgFolder, QDirIterator::NoIteratorFlags);//set iterator
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

bool GraphOutput::fileIsValid(QString fileName)
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

void GraphOutput::getNumberOfSteps()
{
    QFile numbofsteps(numberOfStepsFile);
    if(!numbofsteps.open(QIODevice::ReadOnly)) //open file
    {
        qDebug("Not open");
        return;
    }
    numberOfSteps = numbofsteps.readLine().toInt();//read number of steps from the file
    numbofsteps.close();
}


void GraphOutput::on_prevPushButton_clicked()
{
    changeAutomatically = false;
    ui->stopPushButton->setEnabled(false);

    //find the previous step
    int fileNumber = it->fileName().split(".")[0].toInt() - 1;
    if(fileNumber > numberOfSteps) fileNumber = numberOfSteps-1;
    QString filePath = "";
    if(fileNumber > 9) filePath = QString::number(fileNumber)+".png";
    else filePath = "0" + QString::number(fileNumber)+".png";
    QString path = imgFolder+filePath;
    if(fileNumber > 0)
    {
        setPicture(path);
    }
    else return;
    if(it) delete it;

    //set the current iterator to be the previous step
    it = new QDirIterator(imgFolder, QDirIterator::NoIteratorFlags);
    while(path != it->filePath() && it->hasNext())
    {
        it->next();
    }
}

void GraphOutput::on_nextPushButton_clicked()
{
    //check if the file is valid then show it
    changeAutomatically = false;
    ui->stopPushButton->setEnabled(false);

    if(it->hasNext())
    {
        QString filePath = it->next();
        QString filePath1 = it->fileName();
        if(!fileIsValid(it->fileName())) return;
        setPicture(filePath);
    }
}

void GraphOutput::on_stopPushButton_clicked()
{
    changeAutomatically = false;
    ui->stopPushButton->setEnabled(false);
}

void GraphOutput::setOutput()
{
    QFile output(outputFile);

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

void GraphOutput::on_startPushButton_clicked()
{
    illustrate();
}
