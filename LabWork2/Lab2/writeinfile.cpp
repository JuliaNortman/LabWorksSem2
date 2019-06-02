#include "writeinfile.h"

#include <windows.h>
#include <winbase.h>

Vertex::Vertex(int vertex, QString color, int label)
{
    this->vertex = QString::number(vertex);
    this->color = color;
    this->label = QString::number(label);
}

Edge::Edge(int from, int to, QString color, int label)
{
    this->from = QString::number(from);
    this->to = QString::number(to);
    this->color = color;
    this->label = QString::number(label);
}

WriteInFile::WriteInFile(const Graph& G)
{
    //creating file
    QString path = "LabWorksSem2\\LabWork2\\Lab2\\Files\\00.dat";
    QFile file(path);
    file.remove(); //removes file if it existed before
    if(!file.open(QIODevice::ReadWrite)) //open file
    {
        qDebug("Not open");
    }

    file.write("digraph G {\n");
    file.write("node[shape=\"circle\",style=\"filled\"];\n"); //sets shapes of all nodes

    for(int i = 0; i < G.graph.size();++i)
    {
        file.write((QString::number(i+1)+";\n").toStdString().c_str());
    }

    for(int i = 0; i < G.graph.size(); ++i)
    {
        for(int j = 0; j < G.graph.size(); ++j)
        {
            if(G.graph[i][j] == 0) continue;

            else if(!G.oriented)
            {
                if(j <= i) continue;
                file.write((QString::number(i+1)+"->"+QString::number(j+1)+"[arrowhead=\"none\"];\n").toStdString().c_str());
            }
            else
            {
                if(!G.weighted)
                {
                    file.write((QString::number(i+1)+"->"+QString::number(j+1)+";\n").toStdString().c_str());
                }
                else
                {
                    file.write((QString::number(i+1)+"->"+QString::number(j+1)+"[label=\""
                                +QString::number(G.graph[i][j])+"\"];\n").toStdString().c_str());
                }
            }
        }
    }

    file.write("}");
    file.close();
    //createImage();
    numberOfSteps++;
    writeNumberOfSteps(numberOfSteps);
}

const QString WriteInFile::fileName()
{
    QString fName = "";
    if(numberOfSteps > 9) fName = QString::number(numberOfSteps) + ".dat";
    else fName = "0" + QString::number(numberOfSteps) + ".dat";
    return fName;
}

const QString WriteInFile::prevFileName()
{
    int prevStep = numberOfSteps-1;
    QString fName = "";
    if(prevStep > 9) fName = QString::number(prevStep) + ".dat";
    else fName = "0" + QString::number(prevStep) + ".dat";
    return fName;
}

void WriteEdgeInFile::write(void* e)
{
    Edge* d = static_cast<Edge*>(e);
    QString path = "LabWorksSem2//LabWork2//Lab2//Files//"+prevFileName();
    QString path2  = "LabWorksSem2//LabWork2//Lab2//Files//"+fileName();
    QFile file(path);
    QFile temp(path2);
    if(!file.open(QIODevice::ReadOnly)) //open file
    {
        qDebug("Not open");
        return;
    }
    if(!temp.open(QIODevice::WriteOnly)) //open file
    {
        qDebug("Not open temp");
        return;
    }
    while(!file.atEnd())
    {
        QString line = file.readLine(); //read line from the graphviz.dat
        QString edge = d->from+"->"+d->to;
        if(!line.contains(edge))
        {
            temp.write(line.toStdString().c_str());
        }
        else
        {
            QStringList list = line.split("]");
            if(list.size() == 1) //there is no symbol ']' in the line
            {
                temp.write((edge+"[color=\""+d->color+"\"];\n").toStdString().c_str());
            }
            else
            {
                temp.write((list[0]+",color=\""+d->color+"\"];\n").toStdString().c_str());
            }
        }
    }
    file.close();
    //file.remove();
    temp.close();
    numberOfSteps++;
    writeNumberOfSteps(numberOfSteps);
    //qDebug(std::to_string(numberOfSteps).c_str());
    //temp.rename("LabWorksSem2//LabWork2//Lab2//Files//graphviz.dat");
    //createImage();
}

void WriteVertexInFile::write(void* v)
{
    Vertex* d = static_cast<Vertex*>(v);
    QString path = "LabWorksSem2//LabWork2//Lab2//Files//"+prevFileName();
    QString path2  = "LabWorksSem2//LabWork2//Lab2//Files//"+fileName();
    QFile file(path);
    QFile temp(path2);
    if(!file.open(QIODevice::ReadOnly)) //open file
    {
        qDebug("Not open");
        return;
    }
    if(!temp.open(QIODevice::WriteOnly)) //open file
    {
        qDebug("Not open temp");
        return;
    }
    while(!file.atEnd())
    {
        QString line = file.readLine(); //read line from the graphviz.dat
        QString vertex = line.split(";")[0].split("[")[0]; //in order to get vertex
        if(vertex != d->vertex)
        {
            temp.write(line.toStdString().c_str());
        }
        else
        {
            temp.write((d->vertex+"[color=\""+d->color+"\"];\n").toStdString().c_str());
        }
    }
    file.close();
    //file.remove();
    temp.close();
    numberOfSteps++;
    writeNumberOfSteps(numberOfSteps);
    /*qDebug("nn");
    qDebug(std::to_string(numberOfSteps).c_str());*/
    //temp.rename("LabWorksSem2//LabWork2//Lab2//Files//graphviz.dat");
    //createImage();
}

void WriteInFile::createImage()
{
    //numberOfSteps++;
    /*QString fileName = "";
    if(numberOfSteps > 9) fileName = QString::number(numberOfSteps)+".png";
    else fileName = "0"+QString::number(numberOfSteps)+".png";
    QString pp = "C:\\Users\\HP250\\Documents\\2semester\\Proga\\LABS\\";
    QString graphvizPath = "labworkssem2\\labwork2\\lab2\\graphviz\\release\\bin\\dot.exe";
    QString filePath = "labworkssem2\\labwork2\\lab2\\files\\00.dat";
    QString imagePath = "labworkssem2\\labwork2\\lab2\\Images\\111.png";//+fileName;
    QString myPath = graphvizPath+" -Tpng "+filePath+ " -o " + imagePath;

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessW(myPath.toStdWString().c_str(), nullptr, nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }*/
   /* LPSTARTUPINFOA cif;
    ZeroMemory(&cif,sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;*/
    //const_cast<char*>((" -Tpng "+pp+filePath+ " -o " + pp+imagePath+"\0").toStdString().c_str())

   // CreateProcessA((myPath+"\0").toStdString().c_str(), nullptr, nullptr, nullptr, false, NORMAL_PRIORITY_CLASS, nullptr, nullptr, cif, &pi );

    //system(myPath.toStdString().c_str());
    /*QString pp = "C:\\Users\\HP250\\Documents\\2semester\\Proga\\LABS\\";
    QString graphvizPath = "labworkssem2\\labwork2\\lab2\\graphviz\\release\\bin\\dot.exe";
    QString filePath = "labworkssem2\\labwork2\\lab2\\files\\00.dat";
    QString imagePath = "labworkssem2\\labwork2\\lab2\\Images\\111.png";//+fileName;
    QString myPath = graphvizPath+" -Tpng "+filePath+ " -o " + imagePath;

    if(WinExec(myPath.toStdString().c_str(), SW_HIDE) > 31)
    {
        qDebug("picture was generated");
    }*/
    //ShellExecute(graphvizPath," -Tpng "+filePath+ " -o " + imagePath )
    //ShellExecute("",NULL,"labworkssem2\\labwork2\\lab2\\graphviz\\release\\bin\\dot.exe"," -Tpng "+filePath+ " -o " + imagePath,"", "SW_HIDE");
}

void WriteInFile::writeNumberOfSteps(int numb)
{
    QFile numbofsteps("LabWorksSem2//LabWork2//Lab2//Files//NumberOfSteps.txt");
    if(!numbofsteps.open(QIODevice::WriteOnly)) //open file
    {
        qDebug("Not open");
        return;
    }
    numbofsteps.write(std::to_string(numb).c_str());
    numbofsteps.close();
}
