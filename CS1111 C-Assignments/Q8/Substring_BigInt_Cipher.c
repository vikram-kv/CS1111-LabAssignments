//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXDIGITS 1000//The maximum number of digits a big integer can contain.


//NOTE: This function must be used only if the compiler does not have strrev() in its library.
void Reverse_String(char* str)//Function to reverse a string
{
    int len=strlen(str);//length of the string is computed
    char temp;//temporary variable for swapping purposes
    for(int i=0;i<(len/2);i++)//Loop for going till the middle character in the array
    {
        //Swapping
        temp=str[i];
        str[i]=str[len-1-i];
        str[len-1-i]=temp;
    }
    return ;
}
//Function to read two big integers from a file fname and store the first one as num1 and second one as num2
int Readnum(char* num1,char* num2,const char* fname)
{
    FILE* fp=fopen(fname,"r");//fname is opened in read mode and fp is pointing to the opened buffer
    if(fp==NULL)//Detection of ERROR opening file
    {
        printf("The file doesn't exist.");
        return 0;
    }
    fscanf(fp,"%s",num1);//num1 is scanned as a string
    fgetc(fp);// \n delimiter is removed
    fscanf(fp,"%s",num2);//num2 is scanned as a string
    printf("The numbers stored are:\n%s\n%s",num1,num2);//num1 and num2 are printed to the terminal signaling a successful function call
    fclose(fp);//fname is closed
    return 1;
}

//Function which requests the user for a certain positive integer and prints all the substrings of both the strings of length=read number into fname.
//Returns -1 if user enters erroneous input
//Returns 0 if an error occurs while opening file.
//Else,returns 1.
int Substring(const char* num1,const char* num2,const char* fname)
{
    FILE* fp=fopen(fname,"w");//fname is opened
    if(fp==NULL)//Detection of error opening file
    {
        printf("\nERROR:Failed to open the file.");
        return 0;
    }
    int len,read;//len stores the length of the substrings which the user wants.read is used for storing the return value of scanf()
    printf("\nEnter the length of the substrings which you want:");
    read=scanf("%d",&len);
    getchar();//removal of \n character
    if(read!=1)//if input is invalid
    {
        printf("I cannot understand what you typed.Failing");
        return -1;
    }
    fprintf(fp,"The substrings of length %d of %s:\n",len,num1);
    if(len>strlen(num1))//as requested substrings are of larger length than the string itself
    {
        fprintf(fp,"[NONE]\n");
    }
    else
    {
        //Loop to print all the substrings of length len into fp's buffer
        for(int i=0;i<=(strlen(num1)-len);i++)//i is the index of the substring's first character in the string.
        {
            for(int j=0;j<len;j++)//j is used to print len number of characters starting from num1[i];
            {
                fprintf(fp,"%c",num1[i+j]);
            }
            fprintf(fp,"\n");
        }
    }
    //In similar way as num1, num2's substrings are printed into fp's buffer.
    fprintf(fp,"The substrings of length %d of %s:\n",len,num2);
    if(len>strlen(num2))
    {
        fprintf(fp,"[NONE]\n");
    }
    else
    {
        for(int i=0;i<=(strlen(num2)-len);i++)
        {
            for(int j=0;j<len;j++)
            {
                fprintf(fp,"%c",num2[i+j]);
            }
            fprintf(fp,"\n");
        }
    }
    fclose(fp);//fname is closed.
    printf("\nSubstrings have been successfully stored.");//Signal to the user.
    return 1;
}

//Function which removes trailing zeroes from number in big endian form.To be used in addition and subtraction
void RemoveTrZero(char* num)
{
    int len=strlen(num);//len = length of the number
    int i;//i is for index
    //Loop for identifying the last none zero position
    for(i=len-1;i>0;i--)
    {
        if(num[i]!='0')
            break;
    }
    num[i+1]='\0';//inserting null terminator
    return ;
}

//Function which adds two numbers num1 and num2 and stores the result in num3.All the three numbers are positive
void Add(char* num1,char* num2,char* num3)
{
    strcpy(num3,"0");//num3 is initialized with 0
    strrev(num1);//num1 is converted to big endian form
    strrev(num2);//num2 is converted to big endian form
    int l1=strlen(num1);//l1 is length of num1
    int l2=strlen(num2);//l2 is length of num2
    int larger=0;//larger stores 0 if l1>=l2 and 1 if l2>l1
    if(l2>l1)
        larger=1;
    int result,c1,c2,carry=0;//result atores the result of digitwise addition. It is always converted to a single digits using carry, c1=digit of num1 and c2 =digit of num2
    int i;//i is index variable
    for(i=0;i<=(larger?l2:l1);i++)//test condition is i is less than or equal to the larger among l1 and l2.Loop logic is to perform digitwise addition with carryover .
    {
        if(i>=l1)
        {
            c1=0;//As there is no digit of num1 at that position
        }
        else
        {
            c1=num1[i]-48;//integer whose ascii code is num1[i]
        }
        if(i>=l2)
        {
            c2=0;//As there is no digit of num2 at that position
        }
        else
        {
            c2=num2[i]-48;//integer whose ascii code is num2[i]
        }
        result=carry+c1+c2;//result is found
        carry=0;//carry is initialized
        if(result>=10)//carrying over if result>=10
        {
            carry=1;
            result-=10;
        }
        num3[i]=result+48;//putting character with ascii code as result + 48 in num3[i]
    }
    num3[i]='\0';//Insertion of delimiter
    RemoveTrZero(num3);//Trailing zeroes if any are removed
    strrev(num1);//All numbers are converted to their little endian form
    strrev(num2);
    strrev(num3);
    return;
}

//Function which is used to compare two positive integers num1 and num2
//Returns 1 if num1>num2
//0 if num1=num2
//-1 if num1<num2
int Compare(const char* num1,const char* num2)
{
    int l1=strlen(num1),l2=strlen(num2);//finding lengths of num1 and num2 and storing them in l1 and l2 respectively
    if(l2>l1)
    {
        return -1;//num2>num1
    }
    if(l1>l2)
    {
        return 1;//num1>num2
    }
    else
    {
        return strcmp(num1,num2);//as num1 and num2 are of the same length , strcmp can be used to return the integer corressponding to the cases discussed above
    }
}

//Function to subtract num2 from num1 and store the the result in num3
//num1 and num2 are positive and are in their big endian form and num1>=num2
//l1 and l2 are the respective lengths of num1 and num2
void MagSubtract(const char* num1,const char* num2,char* num3,int l1,int l2)
{
    int borrow,result,c1,c2,i;//borrow will store -1 if borrow is needed from the following digit of num1.i is index.result is the result of subtracting c1 from c2.c1 and c2 are the digits of the numbers num1 and num2 in the ith index.
    borrow=0;
    //Loop to perform num1-num2 by digitwise subtraction with borrow
    for(i=0;i<l1;i++)
    {
        if(i>=l1)//no digit in num1.Defensive programming.This is never possible
        {
        c1=0;
        }
        else
        {
            c1=num1[i]-48;//digit with ascii value equal to num1[i]
        }
        if(i>=l2)//no digit in num2
        {
            c2=0;
        }
        else
        {
            c2=num2[i]-48;//digit with ascii value equal to num2[i]
        }
        result=borrow+c1-c2;
        borrow=0;
        if(result<0)//-ve result needs borrow
        {
            result+=10;
            borrow=-1;
        }
        num3[i]=result+48;
    }
    num3[i]='\0';//insertion of string terminating character
}

//Function which stores the magnitude of the difference num1-num2 in num3
//returns 1 if num1-num2=num3
//returns 0 if num1-num2=-num3
int Subtract(char* num1,char* num2,char* num3)
{
    strcpy(num3,"0");//num3 is initialized
    int l1=strlen(num1);//length of num1 is found
    int l2=strlen(num2);//length of num2 is found
    int larger=Compare(num1,num2);//larger is 1 if num1>num2 and 0 if num1=num2 and -1 if num1<num2
    strrev(num1);//num1 and num2 are converted to their big endian form
    strrev(num2);
    if(larger==0)//num1=num2.=>num3=0
    {
        strcpy(num3,"0");
        return 1;
    }
    else if(larger==1)
    {
        MagSubtract(num1,num2,num3,l1,l2);//num1-num2 is stored in num3
        RemoveTrZero(num3);//trailing zeroes have no value in big endian representation and are removed
    }
    else
    {
        MagSubtract(num2,num1,num3,l2,l1);//num2-num1 is stored in num3
        RemoveTrZero(num3);//trailing zeroes have no value in big endian representation and are removed
    }
    //All numbers are converted to little endian form
    strrev(num1);
    strrev(num2);
    strrev(num3);
    if(larger==1)
        return 1;//sign of num3 is +
    else
        return 0;//sign of num3 is -
}

//Function to multiply the positive number num by the digit digit and store the result in result.
void Single_Digit_Multiply(char* num,int digit,char* result)
{
    int i;
    if(digit==0)//product is 0.
    {
        strcpy(result,"0");
        return;
    }
    char temp[MAXDIGITS];//temp is used to store the partial sum inside the loop
    strcpy(temp,"0");
    //Repetitive addition is performed
    for(i=0;i<digit;i++)
    {
        Add(num,temp,result);
        strcpy(temp,result);//result is now temp for the next iteration
    }
}

//Function to insert requisite number of 0's at the end into the little endian form of a number for multiplication implementation.
//num is the number and count is the number of 0s to be inserted.
void InsertTr_Zeroes(char * num,int count)
{
    int len=strlen(num);//len = length of the number
    int i=1;//i is the loop variable
    //Loop to insert count many 0s at the end
    while(i<=count)
    {
        num[len-1+i]='0';
        i++;
    }
    //Insertion of the null terminator
    num[len+i-1]='\0';
    return;
}

//Function to multiply the positive numbers num1 and num2 and store the result in num3
//num1 , num2 and num3 are in little endian form
void Multiply(char* num1,char* num2,char* num3)
{
    int l1=strlen(num1),l2=strlen(num2);//lengths of num1 and num2 are stored in l1 and l2 respectively.
    int larger=Compare(num1,num2);//larger is 1 if num1>num2 and 0 if num1=num2 and -1 if num1<num2
    strcpy(num3,"0");//num3 is initialized with 0
    if(larger==1)//if num1 is larger than num2
    {
        char temp_result[MAXDIGITS];//temp_result stores the result of multiplying a digit of num2 with the whole of num1
        char partialsum[MAXDIGITS];//partialsum stores the partial result of the multiplication operation at the end of evry iteration
        strcpy(partialsum,"0");//partialsum is initialized
        int i=l2-1;//i is loop variable
        while(i>=0)
        {
            strcpy(temp_result,"0");//temp_result is initialized
            Single_Digit_Multiply(num1,num2[i]-48,temp_result);//a digit of num2 is multiplied with num3
            InsertTr_Zeroes(temp_result,l2-i-1);//the number of trailing 0's corresponding to num2[i]'s place value is inserted
            Add(partialsum,temp_result,num3);//partial sum is stored in num3
            strcpy(partialsum,num3);//the partialsum for next iteration is num3
            i--;
        }
    }
    else
    {
        //Same logic as above but num2 and num1 are interchanged to improve efficiency
        char temp_result[MAXDIGITS];
        char partialsum[MAXDIGITS];
        strcpy(partialsum,"0");
        int i=l1-1;
        while(i>=0)
        {
            Single_Digit_Multiply(num2,num1[i]-48,temp_result);
            InsertTr_Zeroes(temp_result,l1-i-1);
            Add(partialsum,temp_result,num3);
            strcpy(partialsum,num3);
            i--;
        }
    }
}

//Long Division performs num1/num2 and stores the quotient in num3 and remainder in num4
//Implements long Division Algorithm
void LongDivision( char* num1, char* num2,char* num3,char* num4)
{
    char quotient[MAXDIGITS],partialremainder[MAXDIGITS],temp[MAXDIGITS];//quotient will store the quotient,partialremainder will store the remainder,temp will be used for subtraction purposes.
    int digit,digitpos=0,qpos=0,firstborrow=0,len=strlen(num2);//digit stores the digit that has been brought down.digitpos stores the index that can be brought down.firstborrow is boolean variable which stores 1 if a digit is brought down for the first time, else it stores 0.len is the length of num2
    if(Compare(num1,num2)==-1)//if num2>num1 , quotient is 0 and remainder is num1
    {
        strcpy(num3,"0");
        strcpy(num4,num1);
        return;
    }
    strncpy(partialremainder,num1,len);//the first len characters of num1 are copied to partialremainder.
    partialremainder[len]='\0';//insertion of terminator
    digitpos=len;//the position in num2 from where a digit can be brought down
    if(Compare(partialremainder,num2)==-1)//if partialremainder<num2
    {
        partialremainder[len]=num1[len];//an extra digit is brought down
        partialremainder[len+1]='\0';//terminator is inserted
        digitpos=len+1;//digitpos from which a digit can be brought down if needed is raised by 1
    }
    if(digitpos==strlen(num1))//in case there are no more digits to be brought down
    {
        digit=0;//digit is initialized
        //Loop to perform repeated subtraction of num2 from partialremainder(partial remainder)
        while(Compare(partialremainder,num2)!=-1)
        {
            digit++;
            Subtract(partialremainder,num2,temp);
            strcpy(partialremainder,temp);
        }
        quotient[qpos]=digit+48;//quotient's digit is added
        quotient[qpos+1]='\0';//terminator is inserted
        strcpy(num3,quotient);//num3 is quotient
        strcpy(num4,partialremainder);//remainder partialremainder is stored in num4
        return ;
    }
    while(digitpos<strlen(num1))//while there are digits to be brought down
    {
        firstborrow=1;//firstborrow is true. a single digit needs to be brought down at the beginning of every iteration
        if(Compare(partialremainder,num2)==-1)
        {
            int l=strlen(partialremainder);
            partialremainder[l]=num1[digitpos];//a digit is brought down
            digitpos++;//digitpos is incremented by 1
            l++;//the index where \0 needs to be inserted
            partialremainder[l]='\0';//insertion of terminator
            firstborrow=0;//it is not the first borrow anymore
            if(firstborrow!=0)//if another digit needs to be brought down
            {
            strcat(quotient,"0");// a 0 is concatenated to the quotient.
            qpos++;//the index at which a digit of quotient can be put is incremented by 1.
            }
        }
        digit=0;//digit is initialized
        //Loop to perform repeated subtraction of num2 from partialremainder(partial remainder)
        while(Compare(partialremainder,num2)!=-1)
        {
            digit++;
            Subtract(partialremainder,num2,temp);
            strcpy(partialremainder,temp);
        }
        quotient[qpos]=digit+48;//quotient's digit is added
        quotient[qpos+1]='\0';//terminator is inserted
        qpos++;//the position at which teh next digit can be added is incremented by 1.
        if(strcmp(partialremainder,"0")==0)//mag_subtract stores "" incase numbers are equal. To correct that
        {
            strcpy(partialremainder,"");
        }
    }
    if(strcmp(partialremainder,"")==0)//mag_subtract stores "" incase numbers are equal. To correct that
    {
        strcpy(partialremainder,"0");
    }
    strcpy(num3,quotient);//num3 is quotient
    strcpy(num4,partialremainder);//remainder partialremainder is stored in num4
    return ;
}

//Function to write the results of all arithmetic operations into the file fname performed on the numbers num1 and num2.
void Write_ArithmeticOperations(char* num1,char* num2,const char* fname)
{
    FILE* fp=fopen(fname,"w");//fp is opened in write mode
    if(fp==NULL)//Detection of ERROR opening file
    {
        printf("\nERROR: Failed to open the file.");
        return;
    }
    else
    {
        char result1[MAXDIGITS],result2[MAXDIGITS];//result1 will be used for storing results of the operations on num1 and num2.result2 will be used in case two results are produced
        Add(num1,num2,result1);
        fprintf(fp,"\nADDITION:+%s",result1);//addition result
        int sign=Subtract(num1,num2,result1);
        if(sign==1)
        {
            fprintf(fp,"\nSUBTRACTION:+%s",result1);//subtraction result with + sign
        }
        else
        {
            fprintf(fp,"\nSUBTRACTION:-%s",result1);//subtraction result with minus sign
        }
        Multiply(num1,num2,result1);
        fprintf(fp,"\nMultiplication:+%s",result1);//multiplication result
        LongDivision(num1,num2,result1,result2);
        fprintf(fp,"\nDivision: Quotient=+%s\t\tRemainder=+%s",result1,result2);//Division quotient and remainder are printed
        fclose(fp);//fname is closed
        return;
    }
}

//Function to encrypt both the numbers using a user given key,
//to decrypt both the numbers using a user given key
//and store them in fname
void CaesarCipher(const char* num1,const char* num2,const char* fname)
{
    char EKey,DKey;//EKey is key for encryption,DKey is key for decryption
    int read=0;//read is used for storing the return value of scanf
    printf("\nEnter the key for encryption:");
    read=scanf("%c",&EKey);//EKey is obtained
    getchar();//Clear Buffer
    printf("Enter the key for Decryption:");
    read+=scanf("%c",&DKey);//DKey is obtained
    getchar();//Clear Buffer
    if(read!=2)//Invalid Input
    {
        printf("I cannot understand what you have typed.Failing.");
        return ;
    }
    FILE* fp=fopen(fname,"w");//fname is opened in write mode
    if(fp==NULL)//Detection of ERROR opening file
    {
        printf("\nERROR: Failed to open the file.Failing");
        return;
    }
    fprintf(fp,"ASCII VALUE OF KEY FOR ENCRYPTION:%d",EKey);//prints EKey in the file
    fprintf(fp,"\nASCII VALUE OF KEY FOR DECRYPTION:%d\n",DKey);//prints DKey in the file
    int l1=strlen(num1),l2=strlen(num2);
    fprintf(fp,"NUMBER 1:\nEncrypted Form:\n");
    //Loop to store the encrypted form of num1
    for(int i=0;i<l1;i++)
    {
        fprintf(fp,"%c",num1[i]+EKey);
    }
    fprintf(fp,"\nDecrypted Form:\n");
    //Loop to store the decrypted form of num1
    for(int i=0;i<l1;i++)
    {
        fprintf(fp,"%c",num1[i]-DKey);
    }
    fprintf(fp,"\nNUMBER 2:\nEncrypted Form:\n");
    //Loop to store the encrypted form of num2
    for(int i=0;i<l2;i++)
    {
        fprintf(fp,"%c",num2[i]+EKey);
    }
    fprintf(fp,"\nDecrypted Form:\n");
    //Loop to store the decrypted form of num2
    for(int i=0;i<l2;i++)
    {
        fprintf(fp,"%c",num2[i]-DKey);
    }
    fclose(fp);
    return ;
}
int main()
{
    char num1[MAXDIGITS],num2[MAXDIGITS];
    Readnum(num1,num2,"inputNum.txt");//num1 and num2 are read from inputNum.txt
    Substring(num1,num2,"substring.txt");//the substrings are printed into substring.txt
    Write_ArithmeticOperations(num1,num2,"arithmetic.txt");//The results of the arithmetic operations on num1 and num2 are stored in arithmetic.txt
    CaesarCipher(num1,num2,"cipher.txt");//Encrypted and decrypted forms of num1 and num2 are stored in cipher.txt.Both the keys are provided by the user.
    return 0;
}
