//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Maximum length of any line of the palindrome is taken as 200
#define MAXLENGTH 200
//For the static implementation of the program , maximum number of lines in the input file is taken as 100
#define MAXCOUNT 100
//Function which checks whether str is a string which is palindrome or not.returns 1 if it is or else 0.
int Palindrome(const char* str)
{
    int flag=1;//boolean variable whose truth value at the end of the loop indicates whether str is a palindrome or not
    int len=strlen(str);//length of str is stored in len
    for(int i=0;i<len/2;i++)//test condition is for index i less than len/2(integer division resulting in an integer)
    {
        if(tolower(str[i])!=tolower(str[len-i-1]))//case has been ignored in accordance with the sample I/O given in the question
        {
            flag=0;//str is not palindrome
            break;
        }
    }
    return flag;//value of flag is returned.
}
//FUNCTIONS AND TYPE FOR STATIC ARRAY DECLARATIONS:
//Node for static implementation which contains a char array line of size MAXLENGTH and truth variable indicating whether line is a palindrome or not.
struct Node
{
    char line[MAXLENGTH];
    int bool_value;
};
//Function to read line by line from fname and store them in the array stringarray
int SRead(const char* fname,struct Node stringarray[])
{
    FILE* FP=fopen(fname,"r");//fname is opened
    if(FP==NULL)//detection of error opening file
    {
        printf("Failed to open the file.");
        return -1;
    }
    int read;//variable to store value read
    int i=0;//array index variable to keep track of the free location in the array stringarray
    while((read=fgetc(FP))!=EOF)//while it is not EOF
    {
        fseek(FP,-1,SEEK_CUR);//moving the filepointer backward by 1 byte
        fgets(stringarray[i].line,MAXLENGTH,FP);//scanning a line through fgets
        stringarray[i].line[strlen(stringarray[i].line)-1]='\0';//To remove \n at EOL
        stringarray[i].bool_value=Palindrome(stringarray[i].line);//assigning the value of bool_value by calling Palindrome()
        i++;
    }
    fclose(FP);//closing the file
    return i;//returning the number of lines scanned
}
//Function for printing the contents of an array of Nodes named arr whose size is len
void SPrint(struct Node arr[],int len)
{
    for(int i=0;i<len;i++){//i is loop control variable used to traverse across the array arr
        printf("%s\t",arr[i].line);//prints the value of line at i+1th position in arr
        if(arr[i].bool_value==1)//if line is a palindrome
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return;
}
//FUNCTIONS AND TYPE FOR DYNAMIC ARRAY DECLARATIONS:
//Definition of datatype which is same as Node except that it contains a pointer next to its own type
struct DNode
{
    char line[MAXLENGTH];
    int bool_value;
    struct DNode* next;
};
//A function the char array line and bool_value of the location pointed to by ptr.
void Iniitialize(struct DNode* ptr)
{
    strcpy(ptr->line,"NA");//line is assigned NA
    ptr->bool_value=0;//bool_value is assigned 0
    ptr->next=NULL;//next is assigned NULL
}
//Function to read from a file fname and return a pointer to the head of the linked list of DNodes created by it
struct DNode* DRead(const char* fname)
{
    FILE* FP=fopen(fname,"r");//fname is opened
    if(FP==NULL)//detection of error opening file
    {
        printf("Failed to open the file.");
        return NULL;
    }
    struct DNode *head=NULL,*tail=NULL,*temp=NULL;//declarations and assignment of head of the linked list and tail of the linked list. temp is a pointer will be used to point to newly created DNodes.
    int read;//variable to store the value read from the file
    while((read=fgetc(FP))!=EOF)//while it is not EOF
    {
        fseek(FP,-1,SEEK_CUR);//FP is seeked a byte backward
        temp=(struct DNode*)(malloc(sizeof(struct DNode)));//A new DNode is created
        if(temp==NULL)//Failure to allocate memory
        {
            printf("\nMemory Overflow.You may use up to what has already been loaded into heap");
            fclose(FP);//close the file fname
            return head;//returns head of the existing linked list
        }
        Iniitialize(temp);//the new DNode is initialized.
        fgets(temp->line,MAXLENGTH,FP);//line is obtained
        temp->line[strlen(temp->line)-1]='\0';//To remove \n at EOL
        temp->bool_value=Palindrome(temp->line);//value of bool_value is computed
        if(head==NULL)//if list is empty
        {
            head=tail=temp;
        }
        else{
            tail->next=temp;
            tail=temp;
        }
    }
    fclose(FP);//close fname
    return head;// returns head of the created linked list
}
//Function to print the contents of the linked list on the console window through traversal
void DPrint(struct DNode* head)
{
    for(;head!=NULL;head=head->next){
        printf("%s\t",head->line);//prints the line at head
        if(head->bool_value==1)//prints YES if line is palindrome
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");//prints NO if line is not a palindrome
        }
    }
    return;
}
//Function to free the memory allocated to linked list whose first node is at head
void Free_Stack(struct DNode* head)
{
    struct DNode* temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);//memory at temp is freed.
    }
    return;
}

int main()
{
    struct Node stringInfo[MAXCOUNT];
    int count=SRead("palindrome.txt",stringInfo);
    printf("STATIC IMPLEMENTATION:\n");
    SPrint(stringInfo,count);
    struct DNode* head=DRead("palindrome.txt");
    printf("DYNAMIC IMPLEMENTATION:\n");
    DPrint(head);
    Free_Stack(head);
    return 0;
}
