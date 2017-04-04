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

private:
    bool isPosible(int ,int* ,int ,int,int **);
    bool finished(int *color, int n);

};

#endif // PLANNINGEXAM_H
