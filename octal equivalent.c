#include <stdio.h>   
#include<math.h>   

int main()   
{   
    int integer,oct=0,num,i=0;   
    printf("enter integer");   
    scanf("%d",&integer);   
    while(integer!=0)   
    {                
     num=integer%8;   
     oct=oct+num*pow(10,i);    
     integer=integer/8;    
     i++;    
    }     
    printf("enter oct %d", oct);     
    return 0;    
}   

