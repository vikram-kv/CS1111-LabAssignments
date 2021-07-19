#include <stdio.h>//Necessary header file is included

//Function to swap the integers at ptr1 and ptr2 using a temporary variable
void Swap_Using_Temp_Variable(int* ptr1,int* ptr2)
{
    //Doing the swap
    int temp=*ptr1;
    *ptr1=*ptr2;
    *ptr2=temp;
    return ;
}

//Function to swap the integers without a temporary variable
void Swap_Without_Temp_Variable(int *ptr1,int *ptr2)
{
    *ptr1+=*ptr2;
    *ptr2=*ptr1-*ptr2;
    *ptr1-=*ptr2;
}

int main()
{
    int num1,num2;//variables to store two integers
    num1=num2=0;//initialization
    printf("Enter two integers separated by a space:");
    int read=scanf("%d",&num1)+scanf("%d",&num2);//scanning 2 integers
    if(read!=2)
    {
        printf("I could not understand what you have typed.");
        return -1;
    }
    printf("\nBefore swap,number 1=%d,number 2=%d",num1,num2);//Before swap
    Swap_Using_Temp_Variable(&num1,&num2);//Swapping using a temporary variable
    printf("\nAfter swap using a temporary variable,number 1=%d,number 2=%d",num1,num2);//After swap
    Swap_Using_Temp_Variable(&num1,&num2);//Reversing the swap done.
    Swap_Without_Temp_Variable(&num1,&num2);//Swapping without a temporary variable
    printf("\nAfter swap without a temporary variable,number 1=%d,number 2=%d",num1,num2);//After swap
    return 0;
}
