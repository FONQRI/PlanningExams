#include "programmer.h"
#include <iostream>
Programmer::Programmer(QList<Plan *> *verticesList, QObject *parent)
    : QObject(parent)
{
    this->verticesList = verticesList;

    for (Plan *plan : *verticesList)
        {
            verticesColor.push_back(plan->currentColor);
        }

    for (int color : verticesColor)
        {
            std::vector<int>::iterator it;
            it = find(colorsArray.begin(), colorsArray.end(), color);
            if (it == colorsArray.end() && color != -1)
                colorsArray.push_back(color);
        }
}
bool Programmer::isFinished()
{
    int ti;
    for (int i : verticesColor)
        {
            if (i == -1) return false;
            ti = i;
        }

    return true;
}

bool Programmer::isPossible(int index, int color, int size)
{
    for (unsigned int i = 0; i < size; i++)
        if ((connectionArray[index][i] == 1 && verticesColor[i] == color))
            return false;

    return true;
}
void Programmer::paint()
{
    size = verticesList->count();
    deltaG = size - 1;
    verticesColor.clear();
    for (unsigned int i = 0; i < size; i++) verticesColor.push_back(-1);

    for (unsigned int j = 0; j < size; j++)
        {
            vector<int> tempVector;

            for (int i = 0; i < size; i++)
                if (i != j)
                    tempVector.push_back(1);
                else
                    tempVector.push_back(0);

            connectionArray.push_back(tempVector);
        }

    for (int i = 0; i < size; i++)
        {
            if (verticesList->at(i)->firstRelation != nullptr)
                connectionArray[i][verticesList->indexOf(const_cast<Plan *>(
                    verticesList->at(i)->firstRelation))] = 0;
            if (verticesList->at(i)->secondRelation != nullptr)
                connectionArray[i][verticesList->indexOf(const_cast<Plan *>(
                    verticesList->at(i)->secondRelation))] = 0;
            //        verticesList->at(i)->updateInDatabse();
        }

    for (int color = 0; color < deltaG + 1 && !isFinished(); color++)
        {
            colorsArray.push_back(color);
            for (int vertexIndex = 0; vertexIndex < size; vertexIndex++)
                {
                    if (isPossible(vertexIndex, color, size) ||
                        verticesColor[vertexIndex] != -1)
                        {
                            verticesList->at(vertexIndex)->currentColor = color;
                            //        verticesList->at(vertexIndex)->updateInDatabse();
                        }
                }

            if (isFinished()) break;
        }

    setAvailableColors();
}

void Programmer::setAvailableColors()
{
    for (Plan *plan : *verticesList)
        {
            plan->availableColors.clear();
            //        plan->updateInDatabse();
        }

    for (int color : colorsArray)
        for (int vertexIndex = 0; vertexIndex < size; vertexIndex++)
            {
                if (isPossible(vertexIndex, color, size))
                    {
                        verticesList->at(vertexIndex)
                            ->availableColors.push_back(color);
                        //        verticesList->at(vertexIndex)->updateInDatabse();
                    }
            }
}

void Programmer::changeColor(int index, int color)
{
    verticesList->at(index)->currentColor = color;
    //        verticesList->at(index)->updateInDatabse();
    verticesColor[index] = color;
    setAvailableColors();
}

void Programmer::addColor(int index)
{
    int color = colorsArray.size();
    verticesList->at(index)->currentColor = color;
    //        verticesList->at(index)->updateInDatabse();

    colorsArray.push_back(color);
    verticesColor[index] = color;
    setAvailableColors();
}
