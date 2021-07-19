//Inclusion of some header files which are needed
#include <stdio.h>
#include <stdlib.h>

//Definition of some global constant strings which represent names of the towers.They are like name of Tower1(T1) is A and similarly for T2 and T3
const char *T1="A";
const char *T2="B";
const char *T3="C";
//Function prototype which is gonna print the required moves in the output file.Detailed description is above its definition
void Print_TOH(unsigned int,FILE*,const char*,const char*,const char*);

int main()
{
    FILE* fp=fopen("toh_output.txt","w");//fp is declared and defined to be a file pointer to toh_output.txt
    if(fp==NULL)//Detection of error opening file
    {
        printf("ERROR: Failed to open file/File doesn't exist.");
        return -1;
    }
    unsigned int n=0;//A positive integer to store the number of disks
    printf("Enter the total number of disks:");
    scanf("%u",&n);
    Print_TOH(n,fp,T1,T2,T3);//Function call to write the output to the file buffer pointed to by fp.
    fclose(fp);//Output file is closed and delinked.
    return 0;//Successful Termination
}
//Implements a recursive solution for the Towers of Hanoi Problem
//Disks are in Tower 1 initially and need to be moved to Tower 3 at the end
//Note that disks are numbered from 1 to n in increasing order of their masses(or sizes).
void Print_TOH(unsigned int n,FILE* FP,const char *a,const char* b,const char* c)//n is number of disks ; a , b and c stand as arrays which represent names of tower1 , tower 2 and tower 3 respectively.
{
    if(n==1)//1 Disk in 'a' implies it must be moved to 'c' directly and function should return after that.
    {
        fprintf(FP,"Disk 1: %s to %s\n",a,c);
    }
    else
    {
        Print_TOH(n-1,FP,a,c,b);// To move the nth disk from 'a' to 'c', it is understood that the top n-1 disks must be moved from 'a' to 'b' first.
        fprintf(FP,"Disk %d: %s to %s\n",n,a,c);//nth disk is moved from 'a' to 'c'
        Print_TOH(n-1,FP,b,a,c);//the n-1 disks in 'b' are to be moved to 'c' using 'a' during the transfer.
    }
    return;//The return statement is encountered, after all recursive calls are completed.The control then is passed to the main() function.
}
