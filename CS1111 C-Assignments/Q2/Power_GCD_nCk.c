//Necessary Header Files are included.
#include <stdio.h>
#include <stdlib.h>
#include <String.h>

//Definition of a few constants through macros
#define MAX 10   //Max number of digits in the binary representation of the exponent
#define MAXVALUE 100 //Max value of n or k as in nCk.

//Declaration of a few Global Variables
char bin_rep[10];//Used by power(int,int) function to store the binary representation of exponent.
long val[20];//The array where power(int,int) function stores a few values(of which each one is base raised to a power less than exponent) which are used to improve efficiency by avoiding recomputation.
int firsttime=1;//A logic variable whose truth value indicates whether this is the first time the power function is called(1) or not(0).
void Bin_Rep_Calc(int n)//Determines and stores the binary representation of n in bin_rep array
{
    int i=0;//Array index variable
    int val;//used for storing the remainder obtained in the consequent loop
    //Example for the following loop logic
    //We find binary representation through repeated division algorithm
    //Say we want to find 6=1*2^2+1*2^1+0*2^0=(110) [() indicates binary representation]
    //Remainder when 6 is divided by 2 is 0 which is the least significant digit.
    //The quotient 6/2=3=2^1+2^0=(11) is found
    //Now, when 3 is divided by 2 , we get the digit preceding the least digit.
    //This process is repeated till we obtain a 0.
    //The sequence of reminders obtained ordered on the order in which they were found is the big-endian binary representation of the number.
    while(n>0)// Test is that n must be more than 0
    {
        val=n%2;//val stores remainder when n is divided by 2.
        if(val==1)
            bin_rep[i]='1';
        else
            bin_rep[i]='0';
        n/=2;
        i++;
    }
    bin_rep[i]='\0';//Insertion of string_terminating character.
    strrev(bin_rep);//Conversion of big-endian to little endian.
}
void power(int base,int exp)
{
    static int i;//A static integer initialized by compiler to 0 when the function is called for the first time.Used for keeping count of number of recursive function calls and for terminating recursion tree after sufficient funcation calls have been made.
    int len=strlen(bin_rep);//Length of binary representation is found.
    if(firsttime==1)//If it is firsttime
    {
        i=1;//i is assigned 1
        strcpy(bin_rep,"");
        Bin_Rep_Calc(exp);//Binary Rep is computed and stored
        firsttime=0;//It is not the first time for subsequent function calls
    }
    if(i==1)
    {
        val[0]=base;//The first element in the list of values computed by power(int,int) is base^1=base
        i++;//1 call is over.
        power(base,exp);//power(base,exp) is called again.
    }
    else
    {
        switch(bin_rep[i-1])
        {
            case '0':
                val[i-1]=val[i-2]*val[i-2];//if the 'i'th element of bin_rep is 0, val's 'i'th element is found by multiplying the preceding val element with itself.
                break;
            case '1':
                val[i-1]=val[i-2]*val[i-2]*base;//if the 'i'th element of bin_rep is 1, val's 'i'th element is found by multiplying the preceding val element with itself and also base.
                break;
        }
        i++;//Number of calls made is raised by 1.
        if(i==len+1)//Requisite number of calls to find base^exp have been made
        {
            return;//The value of base^exp is stored at the "len"th position of the value array.
        }
        power(base,exp);//power(base,exp) is called again.
    }
}
int GCD(int a,int b)//Computes GCD of two integers a and b through Euclid's Division Lemma
{
    if(a<b)// if b is larger than a , they are to be called by switching their places
    {
        return GCD(b,a);
    }
    else if(a%b==0)//b divides a and b is less than a.So, GCD is b.
    {
        return b;
    }
    else
    {
        return GCD(b,a%b);//Else returns the gcd of b and remainder obtained when a is divided by b.
    }
}
int combination(int n,int k)//Computes nCk through storage of requisite values in a 2D array and the usage of the fact that nCk=(n-1)Ck +(n-1)C(k-1)
{
    if(k>n)
    {
        return -1;// Not defined.
    }
    static int pascaltriangle[MAXVALUE][MAXVALUE];//Initialized to 0 upon first function call.Here,the element at the (n+1)th row and (k+1)th column has the value of nCk
    if(pascaltriangle[n][k]!=0)//If a value has been stored, it is used. Re-computation is avoided.
    {
        return pascaltriangle[n][k];
    }
    if(k==0)
    {
        pascaltriangle[n][k]=1;//Value of nC0 is stored
        return 1;//The above value is also returned
    }
    else if(k==n)
    {
        pascaltriangle[n][k]=1;//Value of nCn is stored
        return 1;//The above value is also returned.
    }
    else
    {
        pascaltriangle[n][k]=combination(n-1,k)+combination(n-1,k-1);//Use of identity to store value of nCk in the triangle
        return pascaltriangle[n][k];//The stored value is also returned.
    }
}
//Function to perform I/O:
void FRead_FWrite(const char* fname)
{
    //Creation and linking of filepointers rfp(for read) and wfp(for write) to their respective files
    FILE* rfp=fopen(fname,"r");
    FILE* wfp=fopen("temp.txt","w");
    if(rfp==NULL||wfp==NULL)//If an error has occurred while opening the files
    {
        printf("\nERROR:Failed to open the file.");
        return ;
    }
    int read;//To store the value read
    int operand1,operand2;//To store the operands read
    char _operator;//To store the operator read
    int result;//To store the result of the operation
    long presult;//To store the long int result of a value returned by power(int,int) function
    while((read=fgetc(rfp))!=EOF)//while it is not EOF
    {
        _operator=read;
        fgetc(rfp);
        fscanf(rfp,"%d",&operand1);
        fgetc(rfp);
        fscanf(rfp,"%d",&operand2);
        fgetc(rfp);//operators and operands are read and stored.
        switch(_operator)
        {
            case 'g':
            case 'G':
                result=GCD(operand1,operand2);//GCD is computed
                break;
            case 'p':
            case 'P':
                firsttime=1;
                power(operand1,operand2);
                presult=val[strlen(bin_rep)-1];//Power(operand1,operand2) is computed
                break;
            case 'b':
            case 'B':
                result=combination(operand1,operand2);//(operand1)C(operand2) is computed
                break;
            default:
                break;
        }
        if(_operator=='P'||_operator=='p')
            fprintf(wfp,"%c %d %d %ld ",_operator,operand1,operand2,presult);
        else
            fprintf(wfp,"%c %d %d %d ",_operator,operand1,operand2,result);//Values are printed into wfp's buffer
    }
    fclose(rfp);//The file linked to rfp is closed and delinked.
    fclose(wfp);//The file linked to wfp is closed and delinked.
    remove(fname);//The file named fname is removed.
    rename("temp.txt",fname);//The new file temp.txt that has been created by this code is renamed as fname
    return;
}
int main()
{
    FRead_FWrite("pgb.txt");
    return 0;//Successful Termination
}
