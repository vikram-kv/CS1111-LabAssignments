//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
//Node is a new type which will be used for dynamically creating a linked list.
//It contains a character (value) and pointer (next) to an instance of it
struct Node
{
    char value;
    struct Node* next;
};
//The function Read reads all the characters from the file fname and returns a pointer to the head of the linked list created dynamically by it.
struct Node* Read(const char* fname)
{
    FILE* FP=fopen(fname,"r");//fname is opened in read mode
    if(FP==NULL)//Detection of error opening file
    {
        printf("File doesn't exist.");
        return NULL;
    }
    int read;//read is used to store a character scanned from the file
    struct Node* head=NULL;//head is a pointer to the first node in the linked list
    struct Node* temp=NULL;//temp will be used as a temporary pointer to newly created nodes
    struct Node* tail=NULL;//tail will be a pointer to the last node in the linked list
    while((read=fgetc(FP))!=EOF)//while it is not EOF. scanned character is stored in read
    {
        temp=(struct Node*)malloc(sizeof(struct Node));//A chunk of sizeof(Node) bytes from heap is allocated and temp is made to pint to it.
        if(temp==NULL)//checking if memory allocation has failed
        {
            printf("\nHeap memory has overflown.What has already been loaded will be printed.");
            fclose(FP);//file fname is closed
            return head;//head to the existing linked list is returned.
        }
        temp->value=read;
        temp->next=NULL;
        if(head==NULL)//if list is empty
        {
            head=tail=temp;//list now has only one node
        }
        else
        {//if list has atleast one node
            tail->next=temp;//new node is linked at the tail end
            tail=temp;//the new tail is the new node
        }
    }
    fclose(FP);//file fname is closed
    return head;//head of the linked list is returned.
}
//Function to print the contents of the linked list to the screen by a loop traversal.
void Print_Stack(struct Node* head)
{
    while(head!=NULL)//while head does not point to the last node's next
    {
        putchar(head->value);//printing the contents at head
        head=head->next;
    }
}
//Function to deallocate the memory assigned to store the linked list
void Free_Stack(struct Node* head)
{
    struct Node* temp;
    temp=head;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;//head is now the first node of the remainder of linked list
        free(temp);//The memory pointed to by temp is freed.
    }
}
int main()
{
    struct Node* head=Read("sentence.txt");//the linked list is created from the contents of the file sentence.txt and the address of its first node is stored in head
    Print_Stack(head);//the contents of the linked list is printed
    Free_Stack(head);//The memory allocated is freed
    return 0;
}
