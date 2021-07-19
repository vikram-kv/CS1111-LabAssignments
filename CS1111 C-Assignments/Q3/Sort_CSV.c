//Necessary header files have been included
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//An user defined constant MAXCOUNT with value 1000 which represents the max number of numbers in Input File
#define MAXCOUNT 1000
//Function Prototypes
int readnum(FILE*,char*);
void Bub_Sort(unsigned int[],int);
int Write_To_File(unsigned int[],const char*,int);
void Print(unsigned int[],int);
int main()
{
    FILE* FP=fopen("sort_num.csv","r");//File Pointer FP is declared and made to point to sort_num.csv after opening it in read mode
    if(FP==NULL)//Check whether input_num.csv has been opened correctly.
    {
        printf("ERROR:Failed to open the file");
        return -1;//Return -1 indicating failed execution of the program
    }
    unsigned int P_Array[MAXCOUNT];//P_Array is an Array of 1000 unsigned integers
    char I_String[20];//I_String is used to temporarily store read numbers in it .
    int _size=0;//_size is indicative of number of elements filled in the array after every iteration.
    while(readnum(FP,I_String)==1)//while filepointer is not at EOF
    {
        sscanf(I_String,"%u",&P_Array[_size]);//sscanf(const char*,const char*,...) is used to scan an unsigned integer from I_String and store it in the _size+1th index of P_Array
        _size++;
        strcpy(I_String,"");//I_String is truncated to 0 length.
        if(_size==MAXCOUNT)//Defensive programming to avoid Array Size Overflow.
            break;
    }
    sscanf(I_String,"%u",&P_Array[_size++]);//Final number is stored
    Bub_Sort(P_Array,_size);//Implements Insertion Sort Algorithm on P_Array whose size is _size.
    Print(P_Array,_size);//Prints the P_Array of size _size in the prescribed format
    if(Write_To_File(P_Array,"sort_num.csv",_size))//If a successful write operation has been performed.
    {
        printf("\nSuccessfully Written!");
        return 0;
    }
    else
    {
        printf("\nERROR: Couldn't write to file.");//Signaling Failure of Write.
        return -1;
    }
}
//readnum is a function which reads digits from the stream pointed to by FP and stores in the array buf.
//return type is boolean . 1 is returned when EOF is not encountered while reading the number, else 0 is returned.
int readnum(FILE* FP,char* buf)
{
    int i=0;//I is index of the location that is free in the buf array.
    int read;//Used to store the character read from FP's buffer
    while((read=fgetc(FP))!=','&&read!=EOF)//Test condition: read is scanned and it is not a ',' or EOF
    {
        buf[i]=read;
        i++;
    }
    buf[i]='\0';//buf is null terminated to make it a string.
    if(read==EOF)//if read is EOF
    {
        return 0;
    }
    return 1;
}
//Implements the bubble sort algorithm
//Invariant:At the end of the 'i'th iteration(outer loop),the last 'i'(after i's update) elements mirror the last 'i'(After update) elemnts of the final sorted array.
void Bub_Sort(unsigned int arr[],int len)
{
    unsigned int temp;
    for(int i=0;i<=(len-1);i++)
    {
        for(int j=0;j<(len-i-1);j++)//Test condition is so because the last 'i' elements are in order.
        {
            if(arr[j]>arr[j+1])//If a preceding element of the array is larger than the consequent one, both are swapped
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    return ;
}
//Function to print the arr in the screen along with their count.
void Print(unsigned int arr[],int len)
{
    int index=0;
    printf("\nThe number of integers found are: %d\nThe sorted list is:\n",len);
    while(index<len)//all elements of the array till the index=len-1 are printed.
    {
        printf("%u ",arr[index]);
        index++;
    }
    return ;
}
//Function to write to the file whose name is fname,the number of integers to be written is len which are stored in arr[]
int Write_To_File(unsigned int arr[],const char* fname,int len)
{
    FILE* FP=fopen(fname,"w");//fname is opened and linked to a filepointer.
    if(FP==NULL)//Checking for error opening file
    {
        return -1;
    }
    else
    {
        int index=0;
        while(index<len-1)//Loop to print all elements excluding the last one with a following comma in adherence to the file format
        {
            fprintf(FP,"%d,",arr[index]);
            index++;
        }
        fprintf(FP,"%d",arr[index]);//Printing the last element without a following comma.
        return 1;
    }
}
