#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QSqlQuery>
#include <QVariant>
#include <algorithm>
#include <vector>

#include "plan.h"

using std::vector;

class Programmer : public QObject
{
    Q_OBJECT
public:
    explicit Programmer(QList<Plan *> *verticesList, QSqlQuery *query,
                        QObject *parent = 0);
    unsigned int size;
    vector<vector<int>> connectionArray;
    unsigned int deltaG;
    vector<int> colorsArray;

private:
    vector<int> verticesColor;
    QSqlQuery *query;
    //  std::vector<int>::iterator it;
    QList<Plan *> *verticesList;
    bool isFinished();
    bool isPossible(int index, int color, int size);

signals:

public slots:
    void paint();
    void setAvailableColors();
    void changeColor(int index, int color);
    void addColor(int index);
};

#endif  // PROGRAMMER_H
