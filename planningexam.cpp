#include "planningexam.h"

PlanningExam::PlanningExam(QObject *parent):QObject(parent)
{


    for (int i=0;i<verticesCountsCPP;i++)
        colorsArray[i]=-1;
    int **isUsed=new int *[verticesCountsCPP];
    for (int i=0;i<verticesCountsCPP;i++)
    {
        isUsed[i]=new int [verticesCountsCPP];
    }

    for (int i=0;i<verticesCountsCPP;i++)
        for(int j=0;j<verticesCountsCPP;j++)
            isUsed[i][j]= -1;

    for (int i=0;i<verticesCountsCPP;i++)
    {
        connectionsArray[i]=new int [verticesCountsCPP];
    }

    for (int i=0;i<verticesCountsCPP;i++)
        for(int j=0;j<verticesCountsCPP;j++)
        {
            if(i==j)
                connectionsArray[i][j]=0;
            else
                connectionsArray[i][j]=1;
        }

    for(int i=0;i<verticesCountsCPP;i++)
        namesArray[i]= to_string(i +1);

    for(int i=0;i<verticesCountsCPP;i++)
    {
        cout<<"enter Vertex "<<namesArray[i] <<" no connactions ( if is down enter 0 or somthing false !!!) : "<<endl;

        for(int j=0;j<verticesCountsCPP -1;j++)
        {
            cin>>entryTemp;
            if (entryTemp < 1 || entryTemp >verticesCountsCPP)
                break;
            connectionsArray[i][entryTemp -1]=connectionsArray[entryTemp -1][i]=0;
        }
    }

    for(int i=0;i<verticesCountsCPP;i++)
    {

        for(int j=0;j<verticesCountsCPP;j++)
        {
            cout<<connectionsArray[i][j]<<"  ";
        }
        cout<<endl;
    }
    // start time
    std::time_t result1 = std::time(nullptr);
    std::cout << " Start Time"<<endl << ctime(&result1);


    //calculating DeltaG
    for(int i=0,sum;i<verticesCountsCPP;i++)
    {
        sum=0;
        for( int j=0;j<verticesCountsCPP;j++)
            sum+=connectionsArray[i][j];
        if(sum>DeltaG)
            DeltaG=sum;
    }

    list <ColorVerticesList> colorList;

    for ( int color=0;color< DeltaG + 1;color++)
    {
        if(finished(colorsArray,verticesCountsCPP))
            break;
        ColorVerticesList colorVerticesList;
        for (int i=0;i<verticesCountsCPP;i++)
        {
            if(colorsArray[i] ==-1)
                if(isPosible(i,colorsArray,color,verticesCountsCPP,connectionsArray))
                {
                    colorVerticesList.AddItem(i);
                    colorsArray[i]=color;
                }
        }
        cout<<"Item(s) of "<<color+1<<" color list is/are : "<<endl;
        colorVerticesList.print(namesArray);
        colorList.insert(colorList.end(),colorVerticesList);
        colorNumbers=colorList.size();
    }

    cout<<" Used color numbers is : "<<colorNumbers<<endl;

    // end time and printing diuration
    std::time_t result2 = std::time(nullptr);
    std::cout << " Finished time"<<endl<< ctime(&result2) <<"diuration :"<<result2 - result1<<"second(s) ."<<endl;
}

int PlanningExam::verticesCount()
{
    return verticesCountsCPP;
}

bool PlanningExam::isPosible(int i,int *color,int col,int n,int **conary)
{
    for (int j=0;j<n;j++)
        if(conary[i][j] != 0)
            if(color[j]==col)
                return 0;
    return 1;
}

bool PlanningExam::finished(int *color,int n)
{
    for (int i=0;i<n;i++)
        if (color[i] == -1)
            return false;
    return true;
}

void PlanningExam::setVerticesCount(int vertexCounts)
{
    verticesCountsCPP = vertexCounts;
    connectionsArray=new int *[verticesCountsCPP];
    for(int i ; i <verticesCountsCPP;i++)
        connectionsArray[i]= new int [verticesCountsCPP];
    colorsArray=new int [verticesCountsCPP];
    namesArray = new string[verticesCountsCPP];

    emit verticesCountChanged();

}
