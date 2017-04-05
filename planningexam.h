#ifndef PLANNINGEXAM_H
#define PLANNINGEXAM_H

#include <iostream>
#include <ctime>
#include <list>
#include <QObject>

#include "colorverticeslist.h"

using namespace std;


class PlanningExam:public QObject
{
    Q_PROPERTY(int verticesCount READ verticesCount WRITE setVerticesCount NOTIFY verticesCountChanged)
    Q_OBJECT
public:
    PlanningExam(QObject *parent = 0);
    int verticesCount();
    void setVerticesCount(int vertexCounts);
    void createSuggestedPlan();
private:
    int verticesCountsCPP;
    int entryTemp = 0 ;
    int **connectionsArray;
    int DeltaG = 0 ;
    string *namesArray;
    int *colorsArray;
    list <ColorVerticesList> colorList;
    ColorVerticesList colorVerticesList;

    bool isPosible(int ,int* ,int ,int,int **);
    bool finished(int *color, int n);
signals:
    void verticesCountChanged();
};

#endif // PLANNINGEXAM_H
