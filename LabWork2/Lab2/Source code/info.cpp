#include "info.h"
#include "ui_info.h"
#include <QFile>

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);

    QString htmlFile = "";
    QFile file(QCoreApplication::applicationDirPath()+"//Files//Info.html");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug("Not open");
        return;
    }

    while(!file.atEnd())
    {
        htmlFile += file.readLine();
    }

    ui->infoTextBrowser->setHtml(htmlFile);
}

Info::~Info()
{
    delete ui;
}

void Info::on_closePushButton_clicked()
{
    this->close();
}
