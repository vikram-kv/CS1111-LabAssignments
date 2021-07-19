//Necessary header files are included.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definition of a new data type student which has a character arrays s_name, hostel and rollno along with a pointer to an object of type student
struct student
{
    char s_name[30];
    char hostel[30];
    char rollno[15];
    struct student* next;
};
//Function to read a line from the buffer of FP and store it in array
//max no of characters that can be stored in array including \0 delimiter is len
//delimiter which separates lines is delim
void getline(FILE* FP,int len,char* array,const char delim)
{
    int read;//read is used to store the value read from FP's buffer
    int index=0;//index is used to keep track of free location in the array
    while((read=fgetc(FP))!=EOF&&read!=delim)
    {
        array[index]=read;
        index++;
        if(index>len-2)
            break;
    }
    array[index]='\0';//instruction of string terminating character '\0'
}
//function to initialize the location( pointed to by ptr)'s data fields with "NA" and next pointer with NULL
void Initialize(struct student* ptr)
{
    strcpy(ptr->s_name,"NA");
    strcpy(ptr->hostel,"NA");
    strcpy(ptr->rollno,"NA");
    ptr->next=NULL;
}
//Function to create the linked list of students and return the address of the first node in the list.
struct student* Read(const char* fname)
{
    FILE* FP=fopen(fname,"r");//fname is opened in read mode
    if(FP==NULL)//Detection of error opening file
    {
        printf("File doesn't exist.");
        return NULL;//Signaling an empty list
    }
    int read;//read is used to detect EOF
    struct student* head=NULL;//pointer to the first node in the linked list
    struct student* temp=NULL;//a pointer that is used to point to a newly created node temporarily
    struct student* tail=NULL;//a pointer to the tail end of the linked list
    while((read=fgetc(FP))!=EOF)//while it is not EOF
    {
        fseek(FP,-1,SEEK_CUR);//FP is seeked a byte backwards
        temp=(struct student*)malloc(sizeof(struct student));//dynamic allocation of memory
        if(temp==NULL)//failure to allocate memory
        {
            printf("\nHeap memory has overflown.What has already been loaded will be printed.");
            fclose(FP);//closing the file fname
            return head;//returning the head of the existing linked list
        }
        Initialize(temp);//initialization of the location pointed to by temp
        getline(FP,30,temp->s_name,'\t');//getting s_name from FP's buffer
        getline(FP,30,temp->hostel,'\t');//getting hostel from FP's buffer
        getline(FP,15,temp->rollno,'\n');//getting rollno from FP's buffer
        if(head==NULL)//if list is empty
        {
            head=tail=temp;
        }
        else
        {
            tail->next=temp;
            tail=temp;
        }
    }
    fclose(FP);//file fname is closed
    return head;//address of the first node of the linked list is returned.
}
//Function to print the contents of the linked list of students whose head is head
void Print(struct student* head)
{
    while(head!=NULL)
    {
        printf("%s\t%s\t%s\n",head->s_name,head->hostel,head->rollno);//Prints name,hostel and rollno separated by a '\t'
        head=head->next;
    }
}
int main()
{
    struct student* head=Read("data.txt");//Creates a linked list of students from data.txt stores the address of the first node in head
    Print(head);//Prints the contents of the linked list of students whose head is head
    return 0;
}
