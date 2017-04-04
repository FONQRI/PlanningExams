#include "planningexam.h"
PlanningExam::PlanningExam()
{
    int vertexCounts;
    cout<<"Please Enter Your Vretexes Number: ";
    cin>>vertexCounts;
    int entryTemp = 0 ;
    int **connectionsArray=new int *[vertexCounts];
    int colorNumbers = 0 ;
    int DeltaG = 0 ;
    string namesArray[vertexCounts];
    int *colorsArray=new int [vertexCounts];
    for (int i=0;i<vertexCounts;i++)
        colorsArray[i]=-1;
    int **isUsed=new int *[vertexCounts];
    for (int i=0;i<vertexCounts;i++)
    {
        isUsed[i]=new int [vertexCounts];
    }

    for (int i=0;i<vertexCounts;i++)
        for(int j=0;j<vertexCounts;j++)
            isUsed[i][j]= -1;

    for (int i=0;i<vertexCounts;i++)
    {
        connectionsArray[i]=new int [vertexCounts];
    }

    for (int i=0;i<vertexCounts;i++)
        for(int j=0;j<vertexCounts;j++)
        {
            if(i==j)
                connectionsArray[i][j]=0;
            else
                connectionsArray[i][j]=1;
        }

    for(int i=0;i<vertexCounts;i++)
        namesArray[i]= to_string(i +1);

    for(int i=0;i<vertexCounts;i++)
    {
        cout<<"enter Vertex "<<namesArray[i] <<" no connactions ( if is down enter 0 or somthing false !!!) : "<<endl;

        for(int j=0;j<vertexCounts -1;j++)
        {
            cin>>entryTemp;
            if (entryTemp < 1 || entryTemp >vertexCounts)
                break;
            connectionsArray[i][entryTemp -1]=connectionsArray[entryTemp -1][i]=0;
        }
    }

    for(int i=0;i<vertexCounts;i++)
    {

        for(int j=0;j<vertexCounts;j++)
        {
            cout<<connectionsArray[i][j]<<"  ";
        }
        cout<<endl;
    }
    // start time
    std::time_t result1 = std::time(nullptr);
    std::cout << " Start Time"<<endl << ctime(&result1);


    //calculating DeltaG
    for(int i=0,sum;i<vertexCounts;i++)
    {
        sum=0;
        for( int j=0;j<vertexCounts;j++)
            sum+=connectionsArray[i][j];
        if(sum>DeltaG)
            DeltaG=sum;
    }

    list <ColorVerticesList> colorList;

    for ( int color=0;color< DeltaG + 1;color++)
    {
        if(finished(colorsArray,vertexCounts))
            break;
        ColorVerticesList colorVerticesList;
        for (int i=0;i<vertexCounts;i++)
        {
            if(colorsArray[i] ==-1)
                if(isPosible(i,colorsArray,color,vertexCounts,connectionsArray))
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
