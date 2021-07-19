//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#define MRC  100 // Defining the max number of rows or columns in any matrix in the program to be a program-wide constant which is 100

//Global variables
int binrary_array[MRC];//This array will be used for determining whether a swap of columns beginning from a given row is allowed without affecting the order of the preceding rows.
//As an example , lets us say MRC =3
//Initially, before any operations, all integers of the array are made 0
//After sorting the elements of the first row along with accompanying column swaps in ASC order, lets say the first element and second element on the first row are equal
//  The array will now store 101
//The 10 indicates for subsequent analysis, column 1 and column 2 my be swapped preserving the order of the first row.

//Function Prototypes:
void row_asc_order(int[][MRC],int,int,int,int,int);
void Matrix_initialise(int[][MRC]);
void swap_col(int[][MRC],int,int,int,int);
void initialise(int[MRC]);
int Check_Row_Sorted(int[][MRC],int,int);
void Print_Matrix(int [][MRC],int,int);

int main(){
    initialise(binrary_array);
    int read,m,n;//m is number of rows, n is number of columns
    read=0;
    printf("Enter the dimensions of the matrix for which you want to know whether the columns can be rearranged in such a way that all the elements in any row are in ascending order:\n");
    read+=scanf("%d",&m);
    read+=scanf("%d",&n);
    //Checking whether the user has entered valid integers
    if(read!=2)
    {
        printf("\n I could not understand what you typed.... Sorry!");
        return 0;
    }
    // Checking whether the entered integers are natural numbers
    else if(m<=0||n<=0)
    {
        printf("Dimensions are always positive... Sorry!");
        return 0;
    }
    //Else
    int Matrix[MRC][MRC];
    //Initializing the elements of the matrix to 0
    Matrix_initialise(Matrix);
    //Obtaining the elements of the matrix from the user through nested for loops
    for(int i=0;i<m;i++)//i is row_index
    {
        for(int j=0;j<n;j++)// j is column_index
        {
            printf("Enter M[%d][%d]:",i,j);
            read=scanf("%d",&Matrix[i][j]);
            // Checking whether the user has entered an integer
            if(read==0)
            {   //printf("%d",Matrix[i][j-1]);
                printf("\nI could not understand what you typed... Try again.\n");
                exit(-1);
            }
        }
    }
    //Validating the obtained input by displaying it on the screen through nested for loops
    Print_Matrix(Matrix,m,n);
    //Checking whether the aim of the program is achievable
    row_asc_order(Matrix,m,n,0,0,n-1);
    if(Check_Row_Sorted(Matrix,m,n)==1)
    {
        printf("\nThe Input Matrix can , through column swapping ,be rearranged to a new matrix where elements in any given row are in ascending order.\nThe rearranged form is:\n");
        Print_Matrix(Matrix,m,n);
    }
    else
    {
        printf("\n The input Matrix is not re-arrangeable.");
    }
    return 0;
}

//Function to initialize the contents of the matrix Matrix with 0
void Matrix_initialise(int Matrix[][MRC])
{
    for(int row_index=0;row_index<MRC;row_index++)
    {
        for(int col_index=0;col_index<MRC;col_index++)
        {
            Matrix[row_index][col_index]=0;
        }
    }
}

//Function which is used to sort the sub-Matrix of Input thorough column swapping only.
//Input matrix has row_size number of rows and column_size number of columns
//The sub-Matrix consists of all the elements whose column_index is between begin_column and end_column with the row_index being greater than or equal to begin_row
//The function calls itself recursively.
void row_asc_order(int Input[][MRC],int row_size,int column_size,int begin_row,int begin_column,int end_column)
{
    if(begin_column==end_column)//Single column sub-Matrix.No swapping is possible
        return;
    else if(begin_row==row_size)//No sub-Matrix exists as it would have 0 rows
        return;
    //Loop to implement bubble sort on the elements on the begin_row with column_index between begin_column and end_column.
    //If the numbers are swapped, their columns are also swapped
    //INVARIANT:at the end of the 'h'th iteration, the first 'h' elements on the begin_row from the one on begin_column are in ascending order
    int i=begin_column;//i is column index variable
    while(i<end_column)
    {
        int j=i+1;
        while(j>begin_column)
        {
            if(Input[begin_row][j]<Input[begin_row][j-1])
            {
                swap_col(Input,row_size,begin_row,j,j-1);
            }
            else
            {
                break;
            }
            j--;
        }
        i++;
    }
    i=begin_column;
    binrary_array[i]=1;//The array element corresponding to i is made 1
    i++;
    //Loop to find which consecutive elements are equal and assign the corresponding integers in the binary_array 1 for the first instance and 0 for the subsequent instances
    //10000 indicates all elements from 1's column to 1's column+4 are equal.
    //We note that at no cost, can a 1 be made 0 in subsequent function calls
    while(i<=end_column)
    {
        if(Input[begin_row][i]==Input[begin_row][i-1]&&binrary_array[i]!=1)
            binrary_array[i]=0;
        else
        {
            binrary_array[i]=1;
        }
        i++;
    }
    i=begin_column;
    //Loop to recursively call the row_asc_order where the entries in begin_row are equal
    while(i<=end_column)
    {
        if(binrary_array[i]==1)//Leading 1 is identified
        {
            int j=i+1;//j will be used for keeping track of the number of 0's
            while(binrary_array[j]!=1&&j<=end_column)
            {
                j++;
            }
            row_asc_order(Input,row_size,column_size,begin_row+1,i,j-1);//Recursive function call with the begin_row now being the next row and begin column being i and end_column being j-1
            i=j-1;//i is j-1 as i will anyhow be incremented by the update statement
        }
        i++;
    }
    return;
}

//Function which will be used to swap the columns whose column indices are c1 and c2 of the matrix Matrix from the row whose index is begin_row_index onwards
//r_size is the number of rows
void swap_col(int Matrix[][MRC],int r_size,int begin_row_index,int c1,int c2)
{
    int row_index=begin_row_index,temp;
    while(row_index<r_size)
    {//the integers in the columns with indices c1 and c2 which are in the row whose index is row_index are swapped
        temp=Matrix[row_index][c1];
        Matrix[row_index][c1]=Matrix[row_index][c2];
        Matrix[row_index][c2]=temp;
        row_index++;
    }
}

//Function which will be used for initializing all the elements of the binary_array to 0
void initialise(int input[MRC])
{
    for(int i=0;i<MRC;i++)
    {
        input[i]=0;
    }
}

//Function which returns the truth value of the statement:All rows of Matrix are in ascending order
//r_size is the number of rows and c_size is the number of columns
int Check_Row_Sorted(int Matrix[][MRC],int r_size,int c_size)
{
    int row_index=0,col_index,flag=1;//row_index = index of the row,col_index is index of the column,flag=variable which is used for breaking out of loops in case a row's elements are not in ascending order
    while(row_index<r_size)
    {
        col_index=0,flag=1;
        while(col_index<c_size-1)
        {
            if(Matrix[row_index][col_index]>Matrix[row_index][col_index+1])//if following element is smaller than preceding element
            {
                flag=0;
                break;
            }
        col_index++;
        }
        if(flag==0)//To detect and exit the outer loop incase the inner loop has encountered a break
            break;
        row_index++;
    }
    if(flag==0)//ALL rows' contents are not in ascending order within a row
        return 0;
    return 1;
}

//Function which uses nested loops to print the matrix Matrix in standard form
//row_size is the number of rows and col_Size is the number of columns
void Print_Matrix(int Matrix[][MRC],int row_size,int col_size)
{
    for(int i=0;i<row_size;i++)
    {
        for(int j=0;j<col_size;j++)
            {
                printf("%d\t",Matrix[i][j]);
            }
        printf("\n");
    }
}
