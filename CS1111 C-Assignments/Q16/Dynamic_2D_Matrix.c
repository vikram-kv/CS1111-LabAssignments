//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
//Function to allocate memory for storing a mxn array of integers[stored in row major form] and depending on letter, use either calloc or malloc for that purpose
int* Alloc(int m ,int n,const char letter)
{
    int *ptr=NULL;//ptr to the first integer in the contiguous memory allocated using malloc or calloc
    switch(letter)
    {
        case 'M':
        case 'm':
            ptr=(int *)(malloc(m*n*sizeof(int)));//allocation of memory
            break;
        case 'c':
        case 'C':
            ptr=(int*)(calloc(m*n,sizeof(int)));//allocation of memory and initialization of it to 0
            break;
        default:
            break;
    }
    return ptr;//returns the address of the first integer in the chunk of memory allocated.
}
//function used to return the address of a particular element in array
int *Array_Elem(int* array,int r_index,int c_index,int dimension)
{
    return (array+r_index*dimension+c_index);//returns the address of the element at row=r_index+1 and column=c_index+1
}
int main()
{
    printf("Enter 'C' for calloc and 'M' for malloc:");
    char choice;
    int read,m,n;//read is used for storing the return value of scanf to find whether scanf operation was successful
    read=scanf("%c",&choice);
    if(read!=1)
    {
        printf("I couldn't understand what you typed.");
        return -1;
    }
    printf("Enter the dimensions of the array m and n:");
    read=scanf("%d",&m);
    read+=scanf("%d",&n);
    if(read!=2)
    {
        printf("I could not understand what you typed.Failing.");
        return -1;
    }
    int *array=Alloc(m,n,choice);//memory for array of dimension m*n is allocated
    if(array==NULL)//detection of failure to allocate memory
    {
        printf("Failed to allocate memory.");
        return -1;
    }
    //Loops to obtain the array elements from the user and store them.i stands for (i+1)th row and j stands for (j+1)th column
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("Enter Matrix[%d][%d]:",i+1,j+1);
            scanf("%d",Array_Elem(array,i,j,n));
        }
    }
    printf("\nThe matrix is:\n");
    //Function to print the matrix on console window
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d\t",*Array_Elem(array,i,j,n));
        }
        printf("\n");//to put a newline at the end of a row
    }
    free(array);//To deallocate memory allocated.
    return 0;
}
