//Required header files are included
#include <stdio.h>
#include <stdlib.h>
//A new data type called Node is created which will contain a value of type int and a pointer next to its own data type
struct Node
{
    int value;
    struct Node* next;
};
//FRead reads from a file fname and returns the value of the head of the linked list it has dynamically created.
struct Node* FRead(const char* fname)
{
    FILE* fp=fopen(fname,"r");//fname is opened and its contents are stored in a buffer pointed to by fp
    if(fp==NULL)//Detection of error opening files
    {
        printf("\nFailed to open the file.");
        return NULL;//Returns NULL signifying linked list is empty
    }
    int read=0;//Used to store the value read from the file
    struct Node* temp;//A temporary ptr variable which is used to point to newly allocated dynamic memory space
    struct Node* head=NULL;//head is used to point to linked list's topmost node and is initially NULL, signifying an empty list.
    struct Node* tail;//tail is used to point to the tail end of the file where newly created nodes can be inserted(like a queue)
    while((read=fgetc(fp))!=EOF)//If it is not EOF
    {
        fseek(fp,-1,SEEK_CUR);//fp is seeked a single byte backward from the location it points to currently
        temp=(struct Node*)(malloc(sizeof(struct Node)));//temp is made to point to newly created dynamic memory.
        if(temp==NULL)//temp is not pointing to any allocated memory.
        {
            printf("Failed to allocate additional memory.");
            return head;//Existing Linked list's head is returned and whereby it is ensured that the already created nodes are accessible and tracked.
        }
        temp->value=0;//value in the new memory is initialised to 0
        temp->next=NULL;//next in new memory is assigned NULL
        fscanf(fp,"%d",&(temp->value));//value in new memory is scanned from the file using fscanf()
        fgetc(fp);//The comma is obtained from the buffer and is thrown out as junk
        if(head==NULL)//if linked list is empty
        {
            head=tail=temp;//head and tail both point to the first node that has been created.
        }
        else
        {
            tail->next=temp;//New node is inserted at the tail end of the linked list
            tail=temp;//Tail is now made to point to the New node
        }
    }
    fclose(fp);//fname is closed and delinked from fp.
    return head;//Linked List's head is returned.
}
//Function to implement merge sort and write to fname
//It merges 2 linked lists whose heads are head1 and head2
void MergeSort(struct Node* head1,struct Node* head2,const char* fname)
{
    FILE* fp=fopen(fname,"w");//fname is opened in write mode
    if(fp==NULL)//Detection of error opening file
    {
        printf("Failed to open the file.");
        return;
    }
    int flag=0;//A flag variable which is used to determine which linked list has remaining nodes at the end of the following loop when one list becomes empty
    //(in the sense that head is pointing to the last element and doesn't imply that all nodes have been deallocated.
    while(1)
    {
        if(head1==NULL)//list1 has become "empty", flag is still 0 indicating this
        {
            break;
        }
        else if(head2==NULL)//list2 has become empty, flag is made 1, and control breaks from the loop
        {
            flag=1;
            break;
        }
        else if(head1->value<=head2->value)//Comparison is made as to which element(head1's value or head2's value is larger)
        {
            fprintf(fp,"%d,",head1->value);
            head1=head1->next;//As head1's value is larger than or equal to head2's value, it is printed into the file and head1 now points to the next element in its list.
        }
        else
        {
            fprintf(fp,"%d,",head2->value);//head2 is made to point to the next element in its list.
            head2=head2->next;
        }
    }
    if(flag==0)//list1 is empty, so list2's values are printed to the file.
    {
        while((head2->next)!=NULL)
        {
            fprintf(fp,"%d,",head2->value);
            head2=head2->next;
        }
        fprintf(fp,"%d",head2->value);
    }
    else
    {//list2 is empty, so so list1's values are printed to the file.
        while((head1->next)!=NULL)
        {
            fprintf(fp,"%d,",head1->value);
            head1=head1->next;
        }
        fprintf(fp,"%d",head1->value);
    }
    fclose(fp);//The file fname is closed and delinked from fp.
    return ;
}
//Function to deallocate the memory allocated to a list.
void Free_Stack(struct Node* head)
{
    struct Node* temp;
    temp=head;
    while(head!=NULL)//Loop is used to free a node while keeping track of the new head.
    {
        temp=head;
        head=head->next;
        free(temp);
    }
}
int main()
{
    struct Node *head1,*head2;
    //Two different linked lists are created from sort_num1.csv and sort_num2.csv
    head1=FRead("sort_num1.csv");
    head2=FRead("sort_num2.csv");
    //The sorted arrays are merged and stored in result.csv
    MergeSort(head1,head2,"result.csv");
    //Memory allocated to head1's list and head2's list is deallocated.
    Free_Stack(head1);
    Free_Stack(head2);
    return 0;
}
