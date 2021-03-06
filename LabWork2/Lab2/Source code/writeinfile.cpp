#include "writeinfile.h"

#include <windows.h>
#include <winbase.h>

Vertex::Vertex(int vertex, QString color, int label)
{
    this->vertex = QString::number(vertex);
    this->color = color;
    //this->label = QString::number(label);
    if(label == 0) this->label = "";
    else this->label = this->vertex + "\n(" +QString::number(label)+")";
}

Edge::Edge(int from, int to, QString color, int label)
{
    this->from = QString::number(from);
    this->to = QString::number(to);
    this->color = color;
    this->label = QString::number(label);
}

WriteInFile::WriteInFile(const Graph& G)
    :g(G)
{
    //creating file
    QString path = fileFolder+"//00.dat";
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
        file.write((QString::number(i)+";\n").toStdString().c_str());
    }

    for(int i = 0; i < G.graph.size(); ++i)
    {
        for(int j = 0; j < G.graph.size(); ++j)
        {
            if(G.graph[i][j] == 0) continue;

            else if(!G.oriented)
            {
                if(j < i) continue;
                if(!G.weighted)
                {
                    file.write((QString::number(i)+"->"+QString::number(j)+"[arrowhead=\"none\"];\n").toStdString().c_str());
                }
                else
                {
                    file.write((QString::number(i)+"->"+QString::number(j)
                                +"[arrowhead=\"none\",label=\""+QString::number(G.graph[i][j])+"\"];\n").toStdString().c_str());
                }

            }
            else
            {
                if(!G.weighted)
                {
                    file.write((QString::number(i)+"->"+QString::number(j)+";\n").toStdString().c_str());
                }
                else
                {
                    file.write((QString::number(i)+"->"+QString::number(j)+"[label=\""
                                +QString::number(G.graph[i][j])+"\"];\n").toStdString().c_str());
                }
            }
        }
    }

    file.write("}");
    file.close();
    CreatePicture(path);
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
    QString path = fileFolder+prevFileName();
    QString path2  = fileFolder+fileName();
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
        QString reverseEdge = d->to+"->"+d->from;
        if(line.contains(edge) || (!g.oriented && line.contains(reverseEdge)))
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
        else
        {
            temp.write(line.toStdString().c_str());
        }

    }
    file.close();
    temp.close();
    CreatePicture(path2);
    numberOfSteps++;
    writeNumberOfSteps(numberOfSteps);
}

void WriteVertexInFile::write(void* v)
{
    Vertex* d = static_cast<Vertex*>(v);
    QString path = fileFolder+prevFileName();
    QString path2  = fileFolder+fileName();
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
            if(d->label == "")
            {
                temp.write((d->vertex+"[color=\""+d->color+"\"];\n").toStdString().c_str());
            }
            else
            {
                temp.write((d->vertex+"[color=\""+d->color+"\",label=\""+d->label+"\"];\n").toStdString().c_str());
            }
        }
    }
    file.close();
    temp.close();
    CreatePicture(path2);
    numberOfSteps++;
    writeNumberOfSteps(numberOfSteps);
}



void WriteInFile::writeNumberOfSteps(int numb)
{
    QFile numbofsteps(numberOfStepsFile);
    if(!numbofsteps.open(QIODevice::WriteOnly)) //open file
    {
        qDebug("Not open");
        return;
    }
    numbofsteps.write(std::to_string(numb).c_str());
    numbofsteps.close();
}

void WriteInFile::CreatePicture(const QString &path)
{
    QString imageName = "";
    if(numberOfSteps+1 > 9) imageName = QString::number(numberOfSteps+1)+".png";
    else imageName = "0"+QString::number(numberOfSteps+1)+".png";
    QString graphvizPath = QCoreApplication::applicationDirPath()+"//Graphviz//release//bin//dot.exe";
    QString filePath = path;
    QString imagePath = imgFolder+imageName;
    QString myPath = graphvizPath+" -Tpng "+filePath+ " -o " + imagePath;

    //lauch graphviz to generate a picture
    WinExec(myPath.toStdString().c_str(), SW_HIDE);
}
