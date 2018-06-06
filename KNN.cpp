/*
    KNN program programmed by Upendra singh bartwal

*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<unistd.h>
using namespace std;
#define Attr 5
#define Ins 120
#define TestA 5
#define TestIns 30
#define K 8

typedef struct dis
{
    float distance;
    int clas;
}dis;
dis distan[120];
bool compare(dis a,dis b)
{
    return a.distance<b.distance;
}
int main()
{

    FILE *ftrain,*ftest;
    //open training file file
    ftrain=fopen("training.txt","r");
    //open testing file
    ftest=fopen("testt.txt","r");
    float train[Ins][Attr];
    float test[TestIns][Attr];
    char str[20];
    int i=0;
    int CountCorrect=0;
    //reading the train data in matrix total attributes 5 all float except one is string
    while((fscanf(ftrain,"%f,%f,%f,%f,%s",&train[i][0],&train[i][1],&train[i][2],&train[i][3],str))!=EOF)
    {
        //comverting class name into number represtation
        if(strcmp(str,"Iris-setosa")==0)
        train[i][4]=0;
        else if(strcmp(str,"Iris-versicolor")==0)
        train[i][4]=1;
        else
        train[i][4]=2;
        i++;
    }
    i=0;
    //reading the testing data in matrix
    while((fscanf(ftest,"%f,%f,%f,%f,%s",&test[i][0],&test[i][1],&test[i][2],&test[i][3],str))!=EOF)
    {
        if(strcmp(str,"Iris-setosa")==0)
        test[i][4]=0;
        else if(strcmp(str,"Iris-versicolor")==0)
        test[i][4]=1;
        else
        test[i][4]=2;
        i++;
    }
    int j,k;
    float temp=0;
    //countVotes to find the population of each class in the k
    int countVote[3]={0};
    //finding euclid distance from each test data entry to the each train data entry
    for (i=0;i<TestIns;i++)
    {
        for (j=0;j<Ins;j++)
        {
            temp=0.0;
            for(k=0;k<Attr-1;k++)
            {
                temp=temp+((test[i][k]-train[j][k])*(test[i][k]-train[j][k]));
            }
            distan[j].distance=sqrt(temp);
            distan[j].clas=train[j][4];
        }
        //shorting the distance(increasingly :so that shortest can be find) from a test point to all train set point
        sort(distan,distan+Ins,compare);

      	for(j=0;j<K;j++)
        {
            countVote[distan[j].clas]++;
        }
        int max=0;
        //finding which class test entry belongs to
        for(j=0;j<3;j++)
        {
            if(countVote[j]>countVote[max])
            max=j;
        }
        if(max==test[i][4])
	{
            //finding accurate one
        	CountCorrect++;

	}
	for(j=0;j<3;j++)
            countVote[j]=0;
    }
    //fidnding accuracy
    cout<<" "<<((float)CountCorrect/TestIns)*100;
}
