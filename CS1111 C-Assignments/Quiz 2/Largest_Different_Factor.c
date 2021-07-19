#include <stdio.h>
#include <math.h>

int large_factor(int);
int main()
{
    int n;
    printf("Enter the number for which you wish to calculate the largest factor different from itself:");
    scanf("%d",&n);
    printf("%d",large_factor(n));
    return 0;
}

int large_factor(int input)
{
    int i=2,flag=1;
    while(i<=(int)sqrt(input))
    {
        if(input%i==0){
            flag=0;
            break;
        }
        i++;
    }
    if(flag==1)
        return 1;
    else{
        return input/i;
    }
}
