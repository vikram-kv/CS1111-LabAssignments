//Necessary header files are included.
#include <stdio.h>
#include <stdlib.h>


//Function prototypes:
float *Array_Elem(float*,int,int,int);
int Gauss_Elim(float*,int,int);


//Function to determine the position of the number at row=r_index+1 and column=col_index+1 in the 2D representation of array assuming that it is stored in ROW_MaAJOR form
//It returns the address of the above number
float *Array_Elem(float* array,int r_index,int c_index,int dimension)
{
    return (array+r_index*dimension+c_index);
}
//Function to perform the Gaussian Elimination on the 2D floating point array which is a square matrix of dimension dimension.
//Starting index indicates the position on the diagonal from where Gaussian elimination must start.
//It is a recursion control variable
//Return type is 0 if det(array) is 0.else if odd number of exchanges have been made, it returns -1. else it returns 1.
int Gauss_Elim(float* array,int s_index,int dimension)
{
    if(s_index==dimension-1)//Recursion termination criteria
    {
        if(*Array_Elem(array,s_index,s_index,dimension)==0.0)
            return 0;
        else
            return 1;
    }
    int flag=1;//flag is used to find whether a swap is possible in case of the diagonal element at row=s_index+1 being 0. It also serves the dual purpose of incorporating a minus sign if a swap is made in the return value
    float ratio=0.0,temp;
    int loc=0;//loc is used for storing the row index of the row which needs to be swapped with the row with row index=s_index
    if(*(Array_Elem(array,s_index,s_index,dimension))==0.0)
    {
        flag=0;//swap is needed.
        for(int i=s_index+1;i<dimension;i++)//loop to find a candidate row for the swap
        {
            if(*Array_Elem(array,i,s_index,dimension)!=0.0)//if a candidate row has been found
            {
                flag=-1;
                loc=i;
                break;
            }
        }
        if(flag==0)
        {
            return Gauss_Elim(array,s_index+1,dimension)*flag;//returns 0. indicating det(array) is 0
        }
        else
        {
            //performing the swap of rows with row index=s_index and loc.
            for(int i=s_index;i<dimension;i++)
            {
                temp=*Array_Elem(array,s_index,i,dimension);
                *Array_Elem(array,s_index,i,dimension)=*Array_Elem(array,loc,i,dimension);
                *Array_Elem(array,loc,i,dimension)=temp;
            }
        }
    }
    //Eliminating the element at row=i+1 and column=s_index+1 across all rows beginning from row whose row_index=s_index+1.
    for(int i=s_index+1;i<dimension;i++)
    {
        ratio=*(Array_Elem(array,i,s_index,dimension))/(*(Array_Elem(array,s_index,s_index,dimension)));
        for(int j=s_index;j<dimension;j++)
            *Array_Elem(array,i,j,dimension)-=ratio*(*Array_Elem(array,s_index,j,dimension));
    }
    return flag*Gauss_Elim(array,s_index+1,dimension);
}
//Function which returns the determinant of 2D array which is a matrix of dimension dimension by performing Gaussian_Elimination on array
float Determinant(float* array,int dimension)
{
    float ret=Gauss_Elim(array,0,dimension);//ret stores the sign of det due to the row exchanges done.It may store 0.0 when det(array)=0
    if(ret==0)
    {
        return 0.0;
    }
    else
    {
        float mag=1.0;
        //Multiplying the elements on the diagonal
        for(int i=0;i<dimension;i++)
            mag*=(*Array_Elem(array,i,i,dimension));
        return ret*mag;
    }
}
//Function to compute the rank of 2D array which is a square matrix of dimension dimension
//Note Rank should be called only after Gaussian Elimination is done through computation of Determinant() function
//Thus array is now in row-echelon form
int Rank(float *array,int dimension)
{
    int rank=0;//Variable which stores Rank
    int flag=0;//flag will be used to find whether a row is entirely 0
    for(int i=0;i<dimension;i++)
    {
        for(int j=0;j<dimension;j++)
        {
            if((*(Array_Elem(array,i,j,dimension)))!=0.0)//The row is not completely 0
            {
                flag=1;
                rank++;//rank is rank +1
                break;//break to go to the next row directly
            }
        }
    }
    return rank;
}


int main()
{
    int dimension;//dimension of square matrix
    printf("Enter the dimension of the square matrix:");
    scanf("%d",&dimension);//gets dimension
    if(dimension<=0)
    {
        printf("Dimension cannot be negative.");
        exit(-1);
    }
    else
    {
        //allocates space for the 2D array which will be implemented in row major form
        float * array=(float*)calloc(dimension*dimension,sizeof(float));
        if(array==NULL)//detection of heap overflow
        {
            printf("\nERROR:Unable to allocate memory for the program.Failing.");
            exit(-1);
        }
        else
        {
            //Obtaining the 2D square matrix
            printf("Enter the Matrix:\n");
            for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                    scanf("%f",Array_Elem(array,i,j,dimension));
            }
            //Printing the determinant and rank of the matrix
            printf("The determinant of the given matrix is:%+.2f\n",Determinant(array,dimension));
            printf("The rank of the given matrix is:%d\n",Rank(array,dimension));
            //Deallocating the allocated memory for array
            free(array);
        }
    }
    return 0;
}
