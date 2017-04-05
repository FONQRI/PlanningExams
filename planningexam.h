#ifndef PLANNINGEXAM_H
#define PLANNINGEXAM_H

#include <iostream>
#include <ctime>
#include <list>

#include "colorverticeslist.h"

using namespace std;


class PlanningExam
{

public:
    PlanningExam();
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
};

#endif // PLANNINGEXAM_H
