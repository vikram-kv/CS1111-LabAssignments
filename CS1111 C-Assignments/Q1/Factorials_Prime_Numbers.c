//Inclusion of necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//INPUT : FPinput.txt
//OUTPUT : FPinput.txt

//Definition of a structure named Node which contains a char operator (F or P or f or p) , an integer operand, and a pointer to the next object of its own type
//which is to be used for dynamic allocation purposes.
struct Node
{
    char _operator;
    int operand;
    struct Node* next;
};
//A function factorial which uses iteration to compute the factorial of its p=argument and returns it.
long factorial(int n)
{
	long result=1;//Result is 1 initially
	for(int i=2;i<=n;i++)//Logic is repetitive multiplication from 2 till the number n itself.
	{
		result*=i;
	}
	return result;//Returns result
}
//A function Check_Prime which checks whether its argument n is prime by recursively calling itself.
//The value of div that is passed when the function is called will be 2
//Then on, the function calls itself after incrementing div by 1 till div becomes larger than n's square root
//During the recursion if div divides n , 0 is returned ,indicating that n is not prime
//Else upon div becoming larger than square root of n, 1  is returned, indicating n is prime.
//LOGIC:ALL COMPOSTIE NUMBERS HAVE A DIVISOR LESS THAN ITS SQUARE ROOT.
int Check_Prime(int n,int div)
{
	if(div>(int)(sqrt(n)))
	{
		return 1; // Number is prime
	}
	else
	{
		if(n%div==0)
		{
			return 0;
		}
		else
		{
			return Check_Prime(n,++div);
		}
	}
}
//This function computes the smallest prime larger than n and returns that value by evaluating Check_Prime for values of i larger than n, starting from n+1
//It breaks from the loop at first instance where Check_Prime returns 1 and returns the corresponding value of i.
int Smallest_Prime_Larger(int n)
{
	int ans;//The smallest prime larger than n
	for(int i=n+1;;i++)//Loop for finding the ans with i as loop variable, initialized to 1 upon loop entry, incremented by 1 as loop update,with no test condition
	{
		if(Check_Prime(i,2)==1)//Checking whether i is prime
		{
			ans=i;
			break;//Exiting from loop
		}
	}
	return ans;
}
int main()
{
    FILE* fp=fopen("FPinput.txt","r");// fp is FILE pointer to FPiNPUT.txt which is opened in read mode
    int read;//Variable for temporarily storing the operator (f or p or F or P) which is read from fp. It is also used to detect EOF
    struct Node *head=NULL,*tail,*temp;//Head is pointer to first node of linked list,tail is pointer to last node,temp will be used as pointer to a newly created node
    while((read=fgetc(fp))!=EOF)//Checking for EOF
    {
        temp=(struct Node*)(malloc(sizeof(struct Node)));//Dynamic memory allocation
        if(temp==NULL)//Detecting Failure to allocate memory from heap
        {
            break;
        }
        temp->_operator=(char)(read);//Storing operator in the location pointed to by temp
        fgetc(fp);//Reading the whitespace and throwing it away.
        fscanf(fp,"%d",&(temp->operand));//Getting the operand following the operator
        fgetc(fp);//Reading whitespace and throwing it away
        temp->next=NULL;//next at the location pointed by temp is made to point to NULL(as it gets inserted in the tail end in our queue implementation
        if(head==NULL)
        {
            head=tail=temp;//if head is null,queue is empty.
        }
        else
        {
            tail->next=temp;//As queue is non-empty,temp is inserted in the tail end
            tail=temp;
        }
    }
    fclose(fp);// FPinput.txt is closed and delinked from the file pointer fp
    fp=fopen("FPinput.txt","w");//The OutputFile is opened in write mode,and hence truncating it to zero length by default
    while(head!=NULL)//Loop to write into the buffer pointed to by fp, all the nodes in queue.
    {
        temp=head;
        head=head->next;
        fprintf(fp,"%c\t",temp->_operator);//writes operator
        fprintf(fp,"%d\t",temp->operand);//writes operand
        switch(temp->_operator)//Takes cases for the operator
        {
            case 'f':
            case 'F':// both f and F lead to factorial of operand being computed and printed
                fprintf(fp,"%ld\t",factorial(temp->operand));
                break;
            case 'p':
            case 'P':// both p and P lead to smallest prime larger than operand being computed and printed
                fprintf(fp,"%ld\t",Smallest_Prime_Larger(temp->operand));
                break;
            default:
                fprintf(fp,"NA\t");//Illegal operand
        }
    }
    fclose(fp);//OutputFile is closed and delinked.
	return 0;//Successful termination.
}
