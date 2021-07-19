//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
//Prototype
void compute_solutions(float[],float[]);

int main(){
    float eqn[2][3],read;//eqn is for storing the coefficients obtained from the user.read is for checking the return value of scanf()
    for(int i=1;i<=2;i++)//Nested loops to obtain the coefficients from the user.
    {
        printf("Enter the values of a,b,c for the %dth linear equation(of the form ax+by=c):",i);
        for(int j=0;j<=2;j++)
        {
            read=scanf("%f",&eqn[i-1][j]);//read value is obtained
            if(read==0){//if a floating point number is not read
                printf("You have not entered an integer . Sorry!");
                exit(-1);
            }
        }
    }
    printf("\n\t");
    compute_solutions(eqn[0],eqn[1]);//The solution(s) is printed
    return 0;
}

//Function to compute and print the solution(s) of the system of equations given as eqn1[0]x+eqn1[1]y=eqn1[2] and eqn2[0]x+eqn2[1]y=eqn2[2]
//It is assumed that the user does not enter invalid equations like 0.0x+0.0y=10
//Uses the Cramer's rule
void compute_solutions(float eqn1[],float eqn2[])
{
    float d1=eqn1[0]*eqn2[1]-eqn1[1]*eqn2[0],d2=eqn1[2]*eqn2[1]-eqn1[1]*eqn2[2],d3=eqn1[0]*eqn2[2]-eqn1[2]*eqn2[0];//d1 is the determinant of the matrix formed by co-efficients of x and y in the equations.d2 is obtained by replacing the x coefficients in d1 with the constants.d3 is obtained by replacing the y coefficients in d1 with the constants.
    if(d1==0.0)
    {
        if(d2==0.0){//Infinite solutions of which two are printed
            printf("You have infinitely many solutions. ");
            if(eqn1[0]!=0&&eqn1[1]!=0)
                printf("A few of which are x=%.4f,y=%.4f and x=%.4f,y=%.4f",1.0,(eqn1[2]-eqn1[0])/eqn1[1], 2.0,(eqn1[2]-2*eqn1[0])/eqn1[1]);
            else if(eqn1[0]==0){
                printf("A few of which are x=1.00 and y=%.4f and x=2.00and y=%.4f",(eqn1[2]/eqn1[1]),(eqn1[2]/eqn1[1]));
            }
            else{
                printf("A few of which are x=%.4f and y=1.00 and x=%.4f and y=2.00",(eqn1[2]/eqn1[0]),(eqn1[2]/eqn1[0]));
            }
            return ;
        }
        else{//No solutions
            printf("You have no solutions.");
            return;
        }
    }
    else
    {//Unique Solution
        printf("The only solution is x=%.4f and y=%.4f",d2/d1,d3/d1);
    }
    return;
}
