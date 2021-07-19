//The necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Definition of a structure called complexnum which represents a complex number through its real and imaginary parts
struct complexnum
{
    double real;
    double imag;
};
//The definition of a function called Print_num which is used to print a complex number c into the buffer of fp.
void Print_num(struct complexnum c,FILE* fp)
{
    if(c.imag==0.0)//c is purely real
        fprintf(fp,"%+.4lf",c.real);//4 digits after decimal point,+ for showing the + sign for positive numbers too.
    else//c is not purely real
        fprintf(fp,"%+.4lf %+.4lfi",c.real,c.imag);
    return;
}
//The definition of a function which reads triplets of integers from fp's buffer.
void Read_Triplets(int *num1,int *num2,int *num3,FILE* fp)
{
    int read;//To store the value scanned from the buffer
    if((read=fgetc(fp))!=EOF)//if it is not EOF
    {
        fseek(fp,-1,SEEK_CUR);//Moving the file pointer one byte backward
        fscanf(fp,"%d",num1);//Reading the first number num1 as an integer
        fgetc(fp);
        fscanf(fp,"%d",num2);//Reading num2 as an integer
        fgetc(fp);
        fscanf(fp,"%d",num3);//Reading num3 as an integer
        fgetc(fp);
    }
    return ;
}
//Function to compute roots of a quadratic equation and store them into fp's buffer
//Equation:ax^2+bx+c=0
//Formula Used:Quadratic Rule- root1=(-b+sqrt(del))/(2*a) and root2=(-b-sqrt(del))/(2*a) where del=b*b-4*a*c
void Find_Roots(int a, int b,int c,FILE* fp)
{
    struct complexnum root1,root2;
    //We note that the sequence of integers cannot contain 0 as it is defined to contain only positive numbers.
    if(a==0.0)//Defensive approach to avoid Undefined computation
    {
        return ;
    }
    double del=(double)b*b-4*a*c;//Discriminant of QE formed as ax^2+bx+c=0
    if(del>=0)//If roots are real
    {
        double sqroot=sqrt(del);
        root1.real=(-b+sqroot)/(2*a);//Value of root1
        root1.imag=0.0;
        root2.real=(-b-sqroot)/(2*a);//Value of root2
        root2.imag=0.0;
    }
    else//roots are complex. sqrt(-1)=i
    {
        double sqroot=sqrt(-del);
        root1.real=root2.real=(double)-b/(2*a);
        root2.imag=-(root1.imag=sqroot/(2*a));
    }
    fprintf(fp,"%d\t%d\t%d\t",a,b,c);//Printing a,b,c to fp's buffer
    Print_num(root1,fp);//Printing root1
    fprintf(fp,"\t");
    Print_num(root2,fp);//Printing root2
    fprintf(fp,"\n");
    return ;
}
int main()
{
    const char* rfname="result.csv";//Input File is result.csv
    const char* wfname="roots.txt";//Output File is roots.txt
    FILE *rfp=fopen("result.csv","r");//Input File is opened in read mode
    if(rfp==NULL)//Detecting error opening file
    {
        printf("\nERROR: Failed to open the file '%s'",rfname);
        return -1;//Signaling Failed execution
    }
    FILE *wfp=fopen("roots.txt","w");//Opening Output File in write mode
    if(wfp==NULL)//Detecting error opening file
    {
        printf("\nERROR: Failed to open the file '%s'",wfname);
        return -1;//Signaling failed execution
    }
    int a,b,c;
    //Loop to scan five triplets (a,b,c) and print them along with the roots of the quadratic equation formed with them as its coefficients
    for(int i=0;i<5;i++)
    {
        Read_Triplets(&a,&b,&c,rfp);
        Find_Roots(a,b,c,wfp);
    }
    fclose(rfp);//Closing Input File
    fclose(wfp);//Closing Output File
    return 0;//Successful execution
}
