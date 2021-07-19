//Necessary header files are included.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Function to determine whether two strings str1 and str2 are equivalent
//Two strings are considered to be equivalent if they are of the same length and don't differ in the frequencies of more than 2 characters
//Function logic is to create arrays which store the frequencies of all characters of both the strings and determine whether they are equivalent
//by comparing the frequencies of all ASCII characters
//Returns the truth value of the statement:str1 and str2 are equivalent if required memory gets allocated dynamically
//else returns -1 indicating insufficient heap memory.
int String_Equivalence(char* str1,char* str2)
{
    int len1=strlen(str1),len2=strlen(str2);//len1 is the length of the first string. len2 is the length of the second string.
    if(len1!=len2)//str1 and str2 are not equivalent
    {
        return 0;
    }
    int *freq1,*freq2;//freq1 will be the frequency array of str1 and freq2 will be the frequency array of str2
    freq1=(int*)(calloc(128,sizeof(int)));//Dynamic allocation of memory needed to store 128 ASCII characters' frequencies.All integers are initialized to 0 automatically.
    if(freq1==NULL)//Detection of failure allocating memory
    {
        return -1;
    }
    freq2=(int*)(calloc(128,sizeof(int)));//Dynamic allocation of memory needed to store 128 ASCII characters' frequencies
    if(freq2==NULL)//Detection of failure allocating memory
    {
        free(freq1);
        return -1;
    }
    char c1,c2;//c1 is character of the str1 that will be read in the loop.Likewise, c2 is for str2
    //Loop to determine the frequencies of all characters in both strings and store them in freq1 and freq2
    for(int i=0;i<len1;i++)
    {
        c1=str1[i];
        c2=str2[i];
        freq1[c1]++;
        freq2[c2]++;
    }
    int count=0,i;//count stores the number of characters whose frequencies don't match, i will be the ascii value of character whose frequencies in the two arrays that will be compared.
    for(i=0;i<128;i++)
    {
        if(freq1[i]!=freq2[i])
            count++;
        if(count==3)//3 characters' frequencies don't match
            break;
    }
    free(freq1);//deallocation of allocated heap memory
    free(freq2);
    if(i!=128)//incomplete termination of loop after encountering a break.
    {
        return 0;//str1 and str2 are not equivalent
    }
    else
    {
        return 1;//str1 and str2 are equivalent
    }
}
//Function to check whether string 2 atr2 is a substring of string 1 str1.
void Check_Substring(char* str1, char* str2)
{
    int len1=strlen(str1),len2=strlen(str2);//len1 is length of str1 and len2 is length of str2
    if(len1<len2)//if str2 is longer than str1
    {
        printf("\n'%s' is not a substring of '%s'",str2,str1);
        return ;
    }
    else if(len1==len2&&strcmp(str1,str2)==0)//If str1 and str2 are of the same length and are equal
    {
        printf("\n'%s' is a substring of '%s'\n",str2,str1);
        printf("The indices are:");
        for(int i=0;i<len1;i++)//As all indices need to be printed
            printf("%d",i+1);
        return ;
    }
    else
    {
        int count =0,flag;//count is to keep track of the total number of times str2 is identified as a substring of str1.
        //flag will be used for identifying possible occurrences of str2 in str1
        for(int i=0;i<=(len1-len2);i++)//i will the loop variable which will be used for moving along str1.beyond i=len1-len2, str2 can't be found in str1, so that will be the test condition
        {
            if(str1[i]==str2[0])//testing the first letter of str2 against the (i+1)th letter of str1
            {
                flag=1;//A possible occurrence of str2 in str1 has been identified
                for(int j=0;j<len2;j++)//checking iteratively if subsequent characters match
                {
                    if(str1[i+j]!=str2[j])//if a j+1th character of str2 doesn't match with i+j+1th character of str1
                    {
                        flag=0;//it is not a possible occurrence of str2 in str1 anymore.
                        break;
                    }
                }
                if(flag==1)//if an occurrence of str2 in str1 has been found
                {
                    count++;
                    if(count==1)//After the first time str2 is found in str1
                    {
                        printf("%s is a substring of %s.",str2,str1);//Statement is printed only once
                    }
                    printf("\nThe indices are:");
                    int k;
                    for(k=0;k<len2-1;k++)//Loop to print the matching indices
                    {
                        printf("%d,",i+k+1);
                    }
                    printf("%d.",i+k+1);
                }
            }
        }
        if(count==0)
        {
            printf("\n'%s' is not a substring of '%s'",str2,str1);
        }
        else if(count>1)
            printf("\nA total of %d matches have been found.",count);
        return ;
    }
}
//A datatype which will be used to store a substring str, its frequency freq and a pointer to its own type for creating a linked list
struct String_Freq_Node
{
    char *str;
    int freq;
    struct String_Freq_Node *next;
};
//Function to return the address of the node whose str matches with match in a linked list whose head is head
//Linear Search algorithm is implemented.
struct String_Freq_Node * Lsearch(struct String_Freq_Node* head,const char* match)
{
    struct String_Freq_Node* node=head;
    while(node!=NULL)
    {
        if(strcmp(node->str,match)==0)
        {
            break;
        }
        node=node->next;
    }
    return node;
}
//Function to find the most frequent substring of a given string.
void Most_Common_Substring(char* str1)
{
    struct String_Freq_Node *head=NULL,*temp=NULL;//head will be the address of the first node of a linked list which will be used to store the set of all distinct substrings of str along with their frquencies
    //temp will function as a temporary pointer to a newly created node.
    int len=strlen(str1);
    char *tempstr;//tempstr will be a string which will be tested against the nodes in the linked list and added to the list if its new.Else,its frequency in the list would be incremented by 1.
    int flag=1;//A variable used for breaking in case of insufficient memory in heap.
    for(int i=1;i<=len&&flag!=0;i++)//i will be used as a length variable in the sense that i would be the length of the tempstr string in the inner loop
    {
        for(int j=0;j<=(len-i);j++)// j would be the beginning index from which tempstr's first character will be obtained
        {
            tempstr=(char*)(calloc(i,sizeof(char)));//memory for tempstr is allocated
            strncpy(tempstr,str1+j,i);//I characters are coopied from the j+1the index of str1 to tempstr
            tempstr[i]='\0';//string terminator is inserted
            temp=Lsearch(head,tempstr);//possible occurrence of tempstr in the linked list is determined.If it has occurred previously, temp gets that node's address. Else, temp would store a NULL
            if(temp==NULL)//if tempstr hasn't occurred already in the list
            {
                //Adding a node with its string as tempstr;
                temp=(struct String_Freq_Node*)(malloc(sizeof(struct String_Freq_Node)));
                if(temp==NULL)
                {
                    printf("Failed to allocate memory.The most common amongst the already loaded ones will be taken.");
                    flag=0;
                    break;
                }
                else
                {
                    temp->next=NULL;
                    temp->freq=1;
                    temp->str=tempstr;
                    if(head==NULL)
                    {
                        head=temp;
                    }
                    else
                    {
                        temp->next=head;
                        head=temp;
                    }
                }
            }
            else
            {
                (temp->freq)++;//frequency is raised by 1
            }
        }
    }
    struct String_Freq_Node* Maxptr;//Pointer to the node in the linked list whose frequency is maximum
    Maxptr=temp=head;
    //Loop to find Maxptr through list traversal
    while(temp!=NULL)
    {
        if((temp->freq)>(Maxptr->freq))
        {
            Maxptr=temp;
        }
        else if((temp->freq)==(Maxptr->freq)&&(strlen(temp->str)>strlen(Maxptr->str)))//if frequencies are equal,the larger string is taken
        {
            Maxptr=temp;
        }
        temp=temp->next;
    }
    //Printing the output
    printf("The most common substring in '%s' is '%s' with a frequency of %d\n",str1,Maxptr->str,Maxptr->freq);
    //Deallocating allocated memory
    while(head!=NULL)
    {
        temp=head;
        free(temp->str);
        free(temp);
        head=head->next;
    }
    return ;
}
int main()
{
    unsigned int len1,len2,read=0;//read is a variable for storing return value of scanf()
    //Obtaining the lengths len1 of the first string and length l2 of the second string.
    printf("Enter the length of the first string:");
    read+=scanf("%u",&len1);
    getchar();//remove \n character
    printf("Enter the length of the second string:");
    read+=scanf("%u",&len2);
    getchar();//remove \n character
    if(read!=2)//If two unsigned integers have not been scanned
    {
        printf("I cannot understand what you typed.");
        return -1;
    }
    char* seq1=NULL;//string seq1 is defined
    char* seq2=NULL;//string seq2 is defined
    //Allocation of necessary memory for seq1 and seq2
    seq1=(char*)(calloc(len1+1,sizeof(char)));
    if(seq1==NULL)
    {
        printf("\nFailed to allocate sufficient memory.Returning.");
        return -1;
    }
    seq2=(char*)(calloc(len2+1,sizeof(char)));
    if(seq2==NULL)
    {
        printf("\nFailed to allocate sufficient memory.Returning.");
        return -1;
    }
    int i;//index variable for obtaining input at index i+1 of a character array
    //Obtaining seq1
    printf("Enter String 1:");
    for(i=0;i<len1;i++)
    {
        seq1[i]=getchar();
    }
    seq1[i]='\0';//insertion of null terminator
    getchar();//removal of \n character
    printf("Enter String 2:");
    for(i=0;i<len2;i++)
    {
        seq2[i]=getchar();
    }
    seq2[i]='\0';
    int choice;//Integer to store user's choice
    //printing of available functions and obtaining choice from the user.
    printf("Here are the choices, Choose any one:\n1.Check whether string 1 and string 2 are equivalent.\n2.Check whether string 2 is a substring of string 1.");
    printf("\n3.Print the most common substring for both the strings.\n");
    read=scanf("%d",&choice);
    if((read!=1)||(choice>3)||(choice<1))//Invalid choice
    {
        printf("Invalid choice.Returning");
        return -1;
    }
    int value;//Variable for holding the return value of string_equivalence function
    switch(choice)
    {
        case 1:
            value=String_Equivalence(seq1,seq2);
            if(value==1)
            {
                printf("The strings are equivalent.");
            }
            else if(value==0)
            {
                printf("The strings are not equivalent.");
            }
            else
            {
                printf("Failed to allocate sufficient memory dynamically.Cant decide equivalence.");
            }
            break;
        case 2:
            Check_Substring(seq1,seq2);
            break;
        case 3:
            Most_Common_Substring(seq1);
            Most_Common_Substring(seq2);
            break;
    }
    //Deallocation of memory allocated to seq1 and seq2
    free(seq1);
    free(seq2);
    return 0;
}
