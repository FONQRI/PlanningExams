#include "colorverticeslist.h"

ColorVerticesList::ColorVerticesList()
{

}
void ColorVerticesList::AddItem(int Index)
{
    if (first == NULL)
    {
        this->first=new colors;
        this->first->ItemIndex=Index;
        this->first->next=NULL;
        this->last=this->first;
    }
    else
    {
        colors *temp=new colors;
        temp->ItemIndex=Index;
        temp->next=NULL;
        this->last->next=temp;
        this->last=temp;
    }
}

void ColorVerticesList::print(string *names)
{
    colors *temp;
    temp=first;
    while(temp !=NULL)
    {
        cout<<names[temp->ItemIndex]<<endl;
        temp=temp->next;
    }
    cout<<endl;
}
