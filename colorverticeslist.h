#ifndef COLORVERTICESLIST_H
#define COLORVERTICESLIST_H
#include <iostream>
#include <string>
using namespace std;
class ColorVerticesList
{


    struct colors
    {
        int ItemIndex;
        colors *next;
    };

private:
    colors *first=NULL;
    colors *last;
public:
    ColorVerticesList();

    void AddItem(int Index);
    void print(string *names);
};

#endif // COLORVERTICESLIST_H
