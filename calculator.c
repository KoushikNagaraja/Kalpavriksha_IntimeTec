#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int calculate(int a,int b,char exp)
{
    switch(exp)
    {
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':if(b==0){printf("division by zero error");exit(0);}return a/b;
        default:printf("Invalid operator");exit(0);
    }
}
int evaluateexpression(const char *character)
{
    int nums[100];
    char operators[100];
    int numsindex=0;
    int operatorindex=0;
    int i=0;
    while(character[i]!='\0')
    {
        if(isspace(character[i]))
        {
            i++;
            continue;
        }
        if(isdigit(character[i]))
        {
            int value=0;
            while(isdigit(character[i]))
            {
                value=value*10+(character[i]-'0');
                i++;
            }
            nums[numsindex++]=value;
        }
        else if(strchr("+-*/",character[i]))
        {
            operators[operatorindex++]=character[i];    
            i++;
        }
        else
        {
            printf("invalid character in expression");exit(0);
        }
    }
    for(int i=0;i<operatorindex;i++)
    {
        if(operators[i]=='*'||operators[i]=='/')
        {
            nums[i]=calculate(nums[i],nums[i+1],operators[i]);
            for(int j=i+1;j<numsindex-1;j++)
            {
                nums[j]=nums[j+1];
            }
            for(int j=i;j<operatorindex-1;j++)
            {
                operators[j]=operators[j+1];
            }
            numsindex--;
            operatorindex--;
            i--;
        }
    }
    for(int i=0;i<operatorindex;i++)
    {
        nums[i+1]=calculate(nums[i],nums[i+1],operators[i]);
    }
    return nums[operatorindex];
}
int main()
{
    char input[100];
    printf("Enter the Expression below : \n");
    fgets(input,sizeof(input),stdin);
    int result=evaluateexpression(input);
    printf("%d",result);
    return 0; 
}
