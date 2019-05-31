#include "writeinfile.h"

WriteInFile::WriteInFile(const Graph& G)
{
    //creating file
    QString path = "LabWorksSem2\\LabWork2\\Lab2\\Files\\graphviz.dat";
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
}

void WriteEdgeInFile::write(void* e)
{
    Edge* d = static_cast<Edge*>(e);
    QString path = "LabWorksSem2//LabWork2//Lab2//Files//graphviz.dat";
    QString path2  = "LabWorksSem2//LabWork2//Lab2//Files//temp.dat";
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
    file.remove();
    temp.close();
    temp.rename("LabWorksSem2//LabWork2//Lab2//Files//graphviz.dat");
    createImage();
    qDebug("After image");
}

void WriteVertexInFile::write(void* v)
{
    Vertex* d = static_cast<Vertex*>(v);
    QString path = "LabWorksSem2//LabWork2//Lab2//Files//graphviz.dat";
    QString path2  = "LabWorksSem2//LabWork2//Lab2//Files//temp.dat";
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
        //qDebug(vertex.toStdString().c_str());
        //qDebug(std::to_string(line.split(";").size()).c_str());
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
    file.remove();
    temp.close();
    temp.rename("LabWorksSem2//LabWork2//Lab2//Files//graphviz.dat");
}

void WriteInFile::createImage()
{
    QString comman_str = "";
    QString filePath = "C:\\Users\\HP250\\Documents\\2semester\\Proga\\LABS\\LabWorksSem2\\LabWork2\\Lab2\\Files\\graphviz.dot";
    QString imagePath = "C:\\Users\\HP250\\Documents\\2semester\\Proga\\LABS\\LabWorksSem2\\LabWork2\\Lab2\\Images\\img.png";
    QString graphvizPath = "C:\\Users\\HP250\\Documents\\2semester\\Proga\\LABS\\LabWorksSem2\\LabWork2\\Lab2\\Graphviz\\release\\bin\\dot.exe";
    //comman_str += "..\\TreeVisualizer\\graphviz\\bin\\dot.exe  -Tpng " + name_str + " -o step_" + std::to_string(global_value - 1) + ".png";
    QString myPath = graphvizPath +  " -v"  + " -o " + imagePath + "-T png " + filePath;
    qDebug(myPath.toStdString().c_str());
    system(myPath.toStdString().c_str());
    //system(graphvizPath.toStdString().c_str());
    //system(myPath.);
}
