#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QVariant>
#include <algorithm>
#include <vector>

#include "plan.h"

using namespace std;

class Programmer : public QObject
{
    Q_OBJECT
public:
    explicit Programmer(QObject *parent = 0);
    int size;
    vector<vector<int>> connectionArray;
    int colorNumbers = 0;
    int deltaG;
    vector<int> colorsArray;

private:
    vector<int> verticesColor;
    std::vector<int>::iterator it;

    bool isFinished();
    bool isPossible(int index, int color, int size);

signals:

public slots:
    void painter(QList<Plan *> *verticesList);
    void availableColors(QList<Plan *> *verticesList);
};

#endif  // PROGRAMMER_H
