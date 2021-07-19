#include <stdio.h>
#define max_length 1000

char num1[max_length],num2[max_length],result[2*max_length];
char sign[3];

void array_initialise(char[],int);
void arithmetic_operation(char[],char[],char[]);
void array_input(char[],int);
void array_output(char[],int,int);
void array_reverse(char[],int);
int main(){
    arithmetic_operation(num1,num2,result);
    return 0;
}
void array_initialise(char Input[],int _size,int number){
for(int i=0;i<_size:i++){
    Input[i]='#';
}
sign[number]='+';
}
void arithmetic_operation(char number_1[],char number_2[],char number_3[]){
    char ch='Y';char choice_operation='+';
    while(ch=='Y'||ch=='y'){
         array_initialise(number_1,max_length,1);
         array_initialise(number_2,max_length,2);
         array_initialise(number_3,2*max_length,3);
         printf("\n Enter the first integer along with the sign of it (\"Max length\"=1000,terminated by a \n(Enter Key):");
         array_input(number_1,1);
         printf("\n You have entered:");
         array_output(number_1,1,max_length);
         printf("\n Enter the second integer along with the sign of it (\"Max length\"=1000,terminated by a \n(Enter Key):");
         array_input(number_2,2);
         printf("You have entered:");
         array_output(number_2,2,max_length);
         printf("\n Enter the symbol of the operation you wish to perform:");
         scanf("%c",choice_operation);
         switch(choice_operation){
            case '+':
                add(number_1,number_2,number_3);
                break;
            case '-':
                sub(number_1,number_2,number_3);
                break;
            case '*':
                mult(number_1,number_2,number_3);
                break;
            case '/':
                divide(number_1,number_2,number_3);
                break;
            default:
                printf("\nI could not understand the operation you wish to perform ... Please try again.");
                break;
         }
         printf("\nDo you wish to continue(Y|N):");
         scanf("%c",ch);
        }
    return;
}
void array_input(char Input[],int number){
sign[number]=getchar();
int i=max_length-1;
while(i>=0)
{
    Input[i]=getchar();
    if(Input[i]=='\n'){
        Input[i]='#';
        break;
    }
    else if(!(Input[i]<=57&&Input[i]>=48))
    {
        printf("\nYou  have not entered a valid digit....Returning...");
        return;
    }
    i--;
}
return;
}
void array_output(char Input[],int number,int _size){
int i=_size-1;
putchar(sign[number]);
while(i>=0){
    if(Input[i]!='#')
     {putchar(Input[i]);
     }
     else{
        break;
     }
     i--;
}
return;}
