#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100
int Freq_Check(char[],char[]);
int main(){
char str[MAX_LENGTH]="abracadabra",substr[MAX_LENGTH]="abrac";
int ans=Freq_Check(str,substr);
printf("%d",ans);
return 0;}

int Freq_Check(char str[],char substr[]){
int l1=strlen(str),l2=strlen(substr);
if(l2>l1)
{
    return 0;
}
if(l1==l2){
    if(strcmp(str,substr)==0){
        return 1;
    }
    else{
        return 0;
    }
}
int freq=0;
for(int i=0;i<=l1-l2;i++)
{
    if(str[i]==substr[0])
    {   int flag=1;
        for(int k=0;k<l2;k++){
            if(str[i+k]!=substr[k]){
                flag=0;
                break;
            }
        }
        if(flag==1){
            freq++;
            i=i+l2-1;
        }
    }
}
return freq;
}





