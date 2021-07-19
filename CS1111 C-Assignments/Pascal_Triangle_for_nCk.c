//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 19//Dimension of the square matrix used for storing the binomial coefficients

//Function Prototypes:
int Compute_Factorial(int,int,int[][MAX_SIZE]);
int Print_In_File(int[][MAX_SIZE],int);

int main()
{
	int bin_coeff[MAX_SIZE][MAX_SIZE];//Array for storing the pascals triangle(only the part which is required for finding nCk, not the whole thing)
	int n,k;//n and k as in nCk
	printf("\nEnter the value of n in nCk:");
	scanf("%d",&n);//n is obtained
	printf("\nEnter the value of k in nCk:");
	scanf("%d",&k);//k is obtained
	if(n<=0||k<0){//Invalid values
	printf("The binomial coefficient is not defined.");
	return -1;
	}
	int row_index=0,col_index=0;
	//Function to initialize the entire 2D array with -1
	for(row_index=0;row_index<MAX_SIZE;row_index++)
	{	for(col_index=0;col_index<MAX_SIZE;col_index++)
		{
		bin_coeff[row_index][col_index]=-1;//Initialization with illegal value -1.
		}
	}
	int answer=Compute_Factorial(n,k,bin_coeff);//answer stores nCk
	printf("The required value nCk is :%d\n",answer);
	if(Print_In_File(bin_coeff,n)==1)//if Pascal's Triangle is printed to the file BIN_COEF.txt successfully
	{
		printf("\nSuccessfully saved in BIN_COEF.txt");
	}
	else
	{//Failed to print the pascal's triangle
		printf("\nFailed to save.");
	}
	return 0;
}

//Function to compute nCk by storing values in Matrix
int Compute_Factorial(int n, int k,int Matrix[][MAX_SIZE])
{
	int row_index=0,col_index=0;
	if(Matrix[0][0]==-1)//if this is the first time the function is called(As 1C1 is not yet stored).
	{
		while(row_index<MAX_SIZE)//Loop to initialize the first column and diagonal of Matrix with 1
		{
			Matrix[row_index][row_index]=1;//As nCn=1
			Matrix[row_index][0]=1;//As nC0=1
			row_index++;
		}
	}
	if(Matrix[n][k]!=-1){//if nCk has already been computed
		return Matrix[n][k];
	}
	else
	{
		Matrix[n][k]=Compute_Factorial(n-1,k,Matrix)+Compute_Factorial(n-1,k-1,Matrix);//nCk=(n-1)Ck+(n-1)C(k-1) if found and stored in its place in Matrix
		return Matrix[n][k];//The stored value is returned.
	}
}

//Function to print the Pascal's triangle, stored in the square matrix called Matrix of dimension n, in a file named BIN_COEF.txt
int Print_In_File(int Matrix[][MAX_SIZE],int n)
{
	FILE* FP=fopen("BIN_COEF.txt","w");//BIN_COEF.txt is opened in write mode
	if(FP==NULL)//Detection of ERROR opening file
	{
		return -1;
	}
	int row_index=0,col_index=0;
	while(row_index<=n)//Loop to traverse across all rows of Matrix
	{
		col_index=0;
		while(col_index<=row_index)//Loop to traverse across all elements in a given row.
		{
			if(Matrix[row_index][col_index]!=-1)
				fprintf(FP,"\t%d",Matrix[row_index][col_index]);
			else
				fprintf(FP,"\t%s","NA");//If Matrix[row_index][col_index] has not been found in the computation of nCk, it is not available
			col_index++;
		}
		fputc('\n',FP);//\n after every row
		row_index++;//Outer loop update statement
	}
	fclose(FP);//BIN_COEF.txt is closed
	return 1;
}


