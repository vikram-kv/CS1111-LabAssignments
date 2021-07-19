//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 10000//Maximum length of the input that can be accepted by the program
int main()
{
    char str[MAXLENGTH];//string that is input by the user
    printf("Enter an input terminated by a ~:");
    int index=0;//index variable of a character in str
    do
    {
        scanf("%c",&str[index]);//the character at index is obtained
        index++;
    }while(str[index-1]!='~'&&index<MAXLENGTH);//if character read is ~, loop is broken.Also, care is taken to avoid overflow
    str[index-1]='\0';//insertion of null terminator
    puts("\nYou have entered :");
    puts(str);//Prints the read string
    int freq_array[26];//array to store the frequencies of different alphabets in str
    int freq_index=0;
    while(freq_index<26)//Loop for initializing the frequencies of all alphabets to 0 initially
    {
        freq_array[freq_index]=0;
        freq_index++;
    }
    index-=2;//index is initialized for loop entry
    int ascii_val;//stores ascii value of character at index in str
    while(index>=0)//Loop for determining the frequencies of different alphabets
    {
        ascii_val=(int) str[index];
        if(ascii_val<=90&&ascii_val>=65)//if str[index] is a uppercase letter
        {
            freq_array[ascii_val-65]++;
        }
        else if(ascii_val>=97&&ascii_val<=122)// if str[index] is lowercase letter
        {
            freq_array[ascii_val-97]++;
        }
        else
        {//all other characters are ignored
        }
    index--;
    }
    freq_index=0;
    while(freq_index<26)//Loop for printing frequencies
    {
        printf("\n The frequency of %c/%c is:%d",(char)(freq_index+65),(char)(freq_index+97),freq_array[freq_index]);
        freq_index++;
    }
    return 0;
}
