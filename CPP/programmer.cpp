#include "programmer.h"

Programmer::Programmer(QList<Plan *> *verticesList, QObject *parent)
    : QObject(parent)
{
    this->verticesList = verticesList;
}
bool Programmer::isFinished()
{
    for (int i : verticesColor)
        if (i == -1) return false;
    return true;
}

bool Programmer::isPossible(int index, int color, int size)
{
    for (unsigned int i = 0; i < size; i++)
        if (connectionArray[index][i] == 1 && colorsArray[i] == color)
            return false;
    return true;
}
void Programmer::paint()
{
    size = verticesList->count();
    deltaG = size - 3;

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
            if (verticesList->at(i)->firstRelation)
                connectionArray[i][verticesList->indexOf(const_cast<Plan *>(
                    verticesList->at(i)->firstRelation))] = 0;
            if (verticesList->at(i)->secondRelation)
                connectionArray[i][verticesList->indexOf(const_cast<Plan *>(
                    verticesList->at(i)->secondRelation))] = 0;
        }
    for (int color = 0; color < deltaG + 1 && !isFinished(); color++)
        {
            colorsArray.push_back(color);
            for (int vertexIndex = 0; vertexIndex < size; vertexIndex++)

                if (isPossible(color, vertexIndex, size))
                    {
                        verticesList->at(vertexIndex)->currentColor = color;
                        verticesColor[vertexIndex] = color;
                    }

            if (!isFinished()) break;
        }
    setAvailableColors();
}

void Programmer::setAvailableColors()
{
    for (int color : colorsArray)
        for (int vertexIndex = 0; vertexIndex < size; vertexIndex++)
            if (isPossible(color, vertexIndex, size))
                verticesList->at(vertexIndex)->availableColors.push_back(color);
}

void Programmer::changeColor(int index, int color)
{
    verticesList->at(index)->currentColor = color;
    verticesColor[index] = color;
    setAvailableColors();
}

void Programmer::addColor(int index)
{
    int color = colorsArray.size();
    verticesList->at(index)->currentColor = color;
    colorsArray.push_back(color);
    verticesColor[index] = color;
}
