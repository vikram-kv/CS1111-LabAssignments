//Necessary header files are included
#include <stdio.h>
#define MAXARRAYSIZE 100//The maximum number of integers the inputted array can have

//Function Prototypes:
float average(int[],int,int);
float avg_Recursion(int[],int,int);


int main()
{
    int Arr[MAXARRAYSIZE+1];//Definition of an array. The first element will be used for summation purposes in the iterative function call.So, an 1 is added in the size
    int size=0,start=0,end=0;//size is the size of the array.start and end are the indices of the sub-array whose average is to be found.
    printf("Enter the number of elements in the array:");
    scanf("%d",&size);//size is obtained
    if(size>MAXARRAYSIZE)//Exceeded the maximum number that can be stored in the array
    {
        return -1;
    }
    Arr[0]=0;//Initialization of the first element
    for(int index=1;index<=size;index++)
    {
        scanf("%d",&Arr[index]);
    }
    printf("\n Enter the value of the starting position and ending position in that order:");
    scanf("%d",&start);//start is obtained
    scanf("%d",&end);//end is obtained
    float avg=average(Arr,start,end);//average by iteration
    printf("\nThe average of the selected elements in the array is(calculated through iteration):%f",avg);
    avg=avg_Recursion(Arr,start,end);//average by recursion
    printf("\nThe average of the selected elements in the array is(calculated through recursion):%f",avg);
    return 0;
}


//Function to return the average of the elements whose indices are in the range [Start,End] of arr through iteration
float average(int arr[],int Start, int End)
{
    int index;//variable to store the index
    if(Start<0||End<0)//illegal values
        return -1.0;
    else if(Start>End)//illegal values
        return 0;
    else
    {
        for(index=Start;index<=End;index++)//Loop to compute the sum of elements in the range [Start,End]
        {
            arr[0]+=arr[index];
        }
    }
    return ((float)arr[0]/(End-Start+1));//average is returned
}


//Function to return the average of the elements whose indices are in the range [start,end] of arr through recursion
float avg_Recursion(int arr[],int Start,int End)
{
    if(Start<0||End<0)//illegal values
        return -1;
    else if(Start>End)//illegal values
        return 0;
    else
    {
        return ((float)(arr[Start]+(End-Start)*avg_Recursion(arr,Start+1,End))/(End-Start+1));//avg of n elements = (first element +(n-1)*(avg of last (n-1) elements))/(n)
    }
}

