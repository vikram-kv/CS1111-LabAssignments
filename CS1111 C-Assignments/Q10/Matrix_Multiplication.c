//Necessary header files are included.
#include <stdio.h>
#include <stdlib.h>
//The max dimension of a column or a row of the matrix is defined to be 100
#define MAX_DIMENSION 100
//Function Prototypes
int Input(float[][MAX_DIMENSION],unsigned int row_size,unsigned int col_size,const char* name);
int Compute_Product(float[][MAX_DIMENSION],unsigned int,unsigned int,float[][MAX_DIMENSION],unsigned int,unsigned int,float[][MAX_DIMENSION]);
void Write(float[][MAX_DIMENSION],unsigned int,unsigned int,float[][MAX_DIMENSION],unsigned int,unsigned int,float[][MAX_DIMENSION],const char*);
int main()
{
    unsigned int row_len1,row_len2,col_len1,col_len2;//Definition of row and column lengths of the two matrices as unsigned integers
    float m1[MAX_DIMENSION][MAX_DIMENSION],m2[MAX_DIMENSION][MAX_DIMENSION],result[MAX_DIMENSION][MAX_DIMENSION];//Definition of two matrices m1 and m2 whose product (is it exists , will be stored in result) as Floating point matrices
    printf("Enter the number of rows and number of columns for the first matrix in that order(MAX 100):");
    //Dimensions of m1 is obtained
    scanf("%u",&row_len1);
    getchar();
    scanf("%u",&col_len1);
    //Detecting Imminent overflow in case of exceeding the MAX_DIMENSION
    if(row_len1>100||col_len1>100)
    {
        printf("You have exceeded the dimensional restraint.Quitting");
        exit(-1);
    }
    //Obtaining input for m1 and checking the truth value of it to find whether the user has actually entered a valid floating point matrix.
    if(!Input(m1,row_len1,col_len1,"MATRIX 1"))
    {
        printf("You have not entered a valid floating point array.Quitting");
        exit(-1);//Exiting in case of invalid matrix
    }
    //Obtaining Input for m2 in a similar way as it was obtained for m1.
    printf("Enter the number of rows and number of columns for the second matrix in that order(MAX 100):");
    scanf("%u",&row_len2);
    getchar();
    scanf("%u",&col_len2);
    if(row_len1>100||col_len1>100)
    {
        printf("\nYou have exceeded the dimensional restraint.Quitting");
        exit(-1);
    }
    if(!Input(m2,row_len2,col_len2,"MATRIX 2"))
    {
        printf("\nYou have not entered a valid floating point array.Quitting");
        exit(-1);
    }
    //The function Compute_Product is called using m1,m2 and their dimensions whose result will be stored in the result matrix if it exists
    if(Compute_Product(m1,row_len1,col_len1,m2,row_len2,col_len2,result))//If it is possible to multiply the matrices
       {
           Write(m1,row_len1,col_len1,m2,row_len2,col_len2,result,"product.txt");//The result is written into product.txt using Write function
            return 0;
       }
    else{
        printf("\nCan't Multiply.");
        return -1;
    }
}
//A function to obtain the values of the elements of a matrix by passing its row size and column size.
//name is used for printing the name of the matrix on the screen while asking for input.
int Input(float matrix[][MAX_DIMENSION],unsigned int row_size,unsigned int col_size,const char* name)
{
    int read;//Variable used for storing the return value of scanf() to detect a successful or failed scan operation
    //Loop to obtain the elements of the matrix where i represents the row index and j represents the column index(both start from 0)
    for(int i=0;i<row_size;i++)
    {
        for(int j=0;j<col_size;j++)
        {
            printf("Enter %s[%d][%d]:",name,i,j);
            read=scanf("%f",&matrix[i][j]);//Scanning the element in the (i+1)th row and (j+1)th column
            if(read!=1)//If scanf() has failed to read a floating point number
                break;
        }
        if(read!=1)//Upon breaking from the inner loop, this also causes an immediate break from the outer loop as well because of the following break statement
            break;
    }
    if(read!=1)
        return 0; //Failed to read a matrix
    else
    {
        return 1;//Successfully read a matrix
    }
}
//Function to compute product of m1 and m2 whose dimensions are r1xc1 and r2xc2 respectively and store it in m3.
//Return type is a integer which is 1 if product exists and 0 if it does not.
int Compute_Product(float m1[][MAX_DIMENSION],unsigned int r1,unsigned int c1,float m2[][MAX_DIMENSION],unsigned int r2,unsigned int c2,float m3[][MAX_DIMENSION])
{
    if(c1!=r2)//Can't multiply
    {
        return 0;
    }
    for(int i=0;i<r1;i++)//i is row index of m3
    {
        for(int j=0;j<c2;j++)//j is column index of m3
        {
            m3[i][j]=0.0;
            for(int k=0;k<c1;k++)//k is used to multiply all elements in (i+1)th row of m1 with their corresponding elements in (j+1)th column of m2 and sum them up.
            {
                m3[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
    return 1;//Product exists
}
//Function to print the matrices m1 ,m2 and m3(product of m1 and m2) in the prescribed format.
//m1's dimension=r1xc1 , m2's dimension=r2xc2 and m3 dimension=r1xc2.
//Name of file in which the matrices are to be printed is fname.
void Write(float m1[][MAX_DIMENSION],unsigned int r1,unsigned int c1,float m2[][MAX_DIMENSION],unsigned int r2,unsigned int c2,float m3[][MAX_DIMENSION],const char* fname)
{
    FILE* FP=fopen(fname,"w");//fname is opened in write mode
    unsigned int max=r2;//a variable called max whose value is currently r2.In the ensuing code, it will be assigned the value of the larger among r1 and r2.
    if(r1>r2)
        max=r1;
    for(int j=0;j<max;j++)//j is the outer loop control variable which is used to print values in the (j+1)th line of the file
    {
        for(int i=1;i<=(c1+c2+c2);i++)//i is the inner loop control variable which is used to print values in the (i+1)th position in a given line
        {
        if(i<c1)//m1 needs to be printed
        {
            if(j>=r1)//nothing in m1 needs to be printed
                fprintf(FP," \t");
            else//there is some value in m1 that needs to be printed
                fprintf(FP,"%.2f\t",m1[j][i-1]);
        }
        else if(i==c1)
        {
            if(j>=r1)
                fprintf(FP," \t\t");//nothing in m1 needs to be printed
            else if(j==0)
                fprintf(FP,"%.2f\tX\t",m1[j][i-1]);//This is used to put a X symbol after m1's 1st row has been printed
            else
                fprintf(FP,"%.2f\t\t",m1[j][i-1]);//there is some value in m1 that needs to be printed along with an extra horizontal tab to leave space between m1 and m2
        }
        else if(i<(c1+c2))
        {
            if(j>=r2)
                fprintf(FP," \t");//nothing in m2 needs to be printed
            else
                fprintf(FP,"%.2f\t",m2[j][i-c1-1]);//there is some value in m2 that needs to be printed
        }
        else if(i==(c1+c2))
        {
            if(j>=r2)
                fprintf(FP," \t\t");//nothing in m2 needs to be printed
            else if(j==0)
                fprintf(FP,"%.2f\t=\t",m2[j][i-c1-1]);//This is used to put a = symbol after m2's 1st row has been printed
            else
                fprintf(FP,"%.2f\t\t",m2[j][i-c1-1]);//there is some value in m1 that needs to be printed along with an extra horizontal tab to leave space between m1 and m2
        }
        else
        {
            if(j>=r1)
                fprintf(FP," \t");//nothing in m3 needs to be printed
            else
                fprintf(FP,"%.2f\t",m3[j][i-c1-c2-1]);//there is some value in m3 that needs to be printed
        }
        }
        fprintf(FP,"\n");//To put newline at the end of every iteration of the outer loop.
    }
    fclose(FP);//FP is closed
    return;
}
