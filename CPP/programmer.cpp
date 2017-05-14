#include "programmer.h"
#include <QDebug>
#include <iostream>

Programmer::Programmer(QList<Plan *> *verticesList, QSqlQuery *query,
					   QObject *parent)
	: QObject(parent)
{
	this->query = query;
	this->verticesList = verticesList;
	std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__ << "\t"
			  << "vertices colors\t" << std::endl;
	for (Plan *plan : *verticesList)
	{
		verticesColor.push_back(plan->currentColor);
		std::clog << plan->currentColor << std::endl;
	}
	std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__ << "\t"
			  << "vertices colors are done\t" << std::endl;
	for (int color : verticesColor)
	{
		std::vector<int>::iterator it;
		it = find(colorsArray.begin(), colorsArray.end(), color);
		if (it == colorsArray.end() && color != -1)
			colorsArray.push_back(color);
	}
	for (int color : colorsArray)
		std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__
				  << "\t"
				  << "color\t" << color << std::endl;
}

bool Programmer::isFinished()
{
	for (int i : verticesColor)
	{
		if (i == -1) return false;
	}
	return true;
}

bool Programmer::isPossible(int index, int color, int size)
{
	std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__ << "\t"
			  << "index\t" << index << "color\t" << color << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__
				  << "\t"
				  << "i\t" << i << std::endl;
		if (index != i)
		{
			std::clog << "index != i" << std::endl;
			if (connectionArray[index][i] == 0)
			{
				std::clog << "connectionArray[index][i] == 0" << std::endl;
				std::clog << "verticesColor[i]\t" << verticesColor[i]
						  << "\t i\t" << i << std::endl;
				if (verticesColor[i] == color)
				{
					std::clog << "verticesColor[i] == color" << std::endl;
					return false;
				}
			}
		}
	}
	std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__ << "\t"
			  << "index\t" << index << "\tcolor\t" << color << "\t is posible"
			  << std::endl;
	return true;
}
void Programmer::paint()
{
	size = verticesList->count();

	deltaG = size - 1;
	verticesColor.clear();
	for (int i = 0; i < size; i++) verticesColor.push_back(-1);

	for (int j = 0; j < size; j++)
	{
		vector<int> tempVector;

		for (int i = 0; i < size; i++) tempVector.push_back(0);

		connectionArray.push_back(tempVector);
	}

	for (int i = 0; i < size; i++)
	{
		if (verticesList->at(i)->firstRelation != nullptr)
		{
			int firstRelation =
				verticesList->indexOf(verticesList->at(i)->firstRelation);
			std::clog << std::endl
					  << "node name \t"
					  << verticesList->at(i)->name.toStdString() << "\t"
					  << verticesList->at(i)->firstRelation->name.toStdString()
					  << "\t index of firstRelation\t" << firstRelation;
			connectionArray[i][firstRelation] = 1;
			connectionArray[firstRelation][i] = 1;
		}
		if (verticesList->at(i)->secondRelation != nullptr)
		{
			int secondRelation =
				verticesList->indexOf(verticesList->at(i)->secondRelation);
			std::clog << std::endl
					  << "node name \t"
					  << verticesList->at(i)->name.toStdString() << "\t"
					  << verticesList->at(i)->secondRelation->name.toStdString()
					  << "\t index of secondRelation\t" << secondRelation;
			connectionArray[i][secondRelation] = 1;
			connectionArray[secondRelation][i] = 1;
		}
	}

	for (int i = 0; i < size; i++)
	{
		std::clog << std::endl;
		for (int j = 0; j < size; j++) std::clog << connectionArray.at(i).at(j);
    }
	std::clog << std::endl << "printing array finished" << std::endl;

	for (int color = 0; !isFinished(); color++)
	{
		colorsArray.push_back(color);
		for (int vertexIndex = 0; vertexIndex < size; vertexIndex++)
		{
			if (verticesColor[vertexIndex] == -1 &&
				isPossible(vertexIndex, color, size))
			{
				verticesList->at(vertexIndex)->currentColor = color;
				verticesColor[vertexIndex] = color;
				verticesList->at(vertexIndex)->updateColorInDatabse(query);
			}
		}

		if (isFinished()) break;
	}

	for (int colorArray : verticesColor) std::clog << "\tcolor :" << colorArray;
	setAvailableColors();
}

void Programmer::setAvailableColors()
{
	for (Plan *plan : *verticesList)
	{
		plan->availableColors.clear();
		plan->updateColorInDatabse(query);
	}

	for (int color : colorsArray)
		for (int vertexIndex = 0; vertexIndex < size; vertexIndex++)
		{
			if (isPossible(vertexIndex, color, size))
			{
				verticesList->at(vertexIndex)->availableColors.push_back(color);
				verticesList->at(vertexIndex)->updateColorListInDatabse(query);
			}
		}
}

void Programmer::changeColor(int index, int color)
{
	verticesList->at(index)->currentColor = color;
	verticesColor[index] = color;
	setAvailableColors();
	std::clog << __LINE__ << "\t" << __FUNCTION__ << "\t" << __FILE__ << "\t"
			  << "index\t" << index << "\tcolor\t" << color
			  << "\t color changed" << std::endl;
}

void Programmer::addColor(int index)
{
	int color = colorsArray.size();
	verticesList->at(index)->currentColor = color;
	colorsArray.push_back(color);
	verticesColor[index] = color;
	setAvailableColors();
}
