//Siddharth Rakesh
//11CS30036

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

typedef struct tag1   //required struct for integer linked list
{
    int oper;
    struct tag1* next;
}opnd;

opnd* opnt = NULL;
opnd* opnb = NULL;

typedef struct tag   //requred struct for operator linked list
{
    char oper;
    struct tag* next;
}otor;

otor* oprt = NULL;
otor* oprb = NULL;

void pushnum(int Number)  //function to push number in integer stack
{         
    opnd* entry = (opnd*)malloc(sizeof(opnd));
    entry->oper = Number;
    entry->next = NULL;
         
    if(opnb==NULL)
    {
      opnb = entry;
      opnt = entry;
    }
    else
    {
      opnt->next = entry;
      opnt = entry;
    }
}
    
int popnum()   //function to pop number from integer stack
{    
    int num;
    if(opnt==NULL)
    {
        printf("Stack empty...");
        return 0;
    }
    if(opnt==opnb)
    {
        num = opnt->oper;
        opnt = NULL;
        opnb = NULL;
        return num;
    }
    opnd* t = opnb;
    
    while(t->next!=opnt) 
    t=t->next;
        
    num = opnt->oper;
    opnt = t;
    opnt->next = NULL;
 
    return num;
}

void push(int number)  //function to push charcter in operator stack
{
     otor* entry = (otor*)malloc(sizeof(otor));
     entry->oper = number;
     entry->next = NULL;
     
     if(oprb==NULL)
     {
        oprb = entry;
        oprt = entry;
     }
     else
     {
        oprt->next = entry;
        oprt = entry;
     }
}

char pop()  //function to pop character from operator stack
{
    char ch;
    if(oprt==NULL)
    {
     printf("Stack empty...");
     return ' ';
    }
    if(oprt==oprb)
    {
      ch = oprt->oper;
      oprt = NULL;
      oprb = NULL;
      return ch;
    }
    otor* t = oprb;
    while(t->next!=oprt) 
    t=t->next;
    
    ch = oprt->oper;
    oprt = t;
    oprt->next = NULL;
    return ch;
}

void InfixToPostfix(char* infix,char* postfix)  //function to convert the infix expression to postfix
{
    int i,j=0;
    char c;

    for(i=0;i<strlen(infix);i++)
    {
       if(isdigit(infix[i])!=0)   //if current character is a digit
       {
          postfix[j]=infix[i];
          j++;
          if(infix[i+1]=='+'||infix[i+1]=='-'||infix[i+1]=='*'||infix[i+1]=='/')
          {
             postfix[j]=' ';
             j++;
          }
       }
       else   //if not a digit
       {
          if(infix[i]=='(')
          push('(');
          
          else if(infix[i]=='+'||infix[i]=='-')   //as * and / have precedence over + and -
          {
              while(oprt!=NULL&&oprt->oper!='(')
              {
                 c=pop();
                 postfix[j]=c;
                 j++;
              }
              push(infix[i]);
          }
          else if((infix[i]=='*'||infix[i]=='/')&&oprt!=NULL&&(oprt->oper=='*'||oprt->oper=='/'))
          {
              while(oprt!=NULL&&(oprt->oper=='*'||oprt->oper=='/'))
              {
                 c=pop();
                 postfix[j]=c;
                 j++;
              }
              push(infix[i]);
          }
          else if(infix[i]!=')')
          { 
             push(infix[i]);
          }
          else
          {
             while(oprt!=NULL)
             {
                 c = pop();
                 if(c=='(')
                   break;
             
                 else 
                 {
                  postfix[j]=c;
                  j++;
                 }
             } 
          }
       }
       
    }
    
    while(oprt!=NULL)
    {
       c = pop();
       postfix[j] = c;
       j++;
    }
    
    postfix[j]='\0';  //adding null at end
}

int EvaluatePostfix(char* postfix)    //function to evaluate postfix expression
{
    char numb[5];
    int i,j,flag=0;
    int a,b;
    int res;

    for(i=0;i<strlen(postfix);i++)
    {
       if(isdigit(postfix[i])!=0)
       {
           j=0;
           while(isdigit(postfix[i])!=0)
           {
            numb[j]=postfix[i];
            j++;i++;
           }
           i--;
           numb[j]='\0';
           pushnum(atoi(numb));  //converting char array to a number
       }
       
       else
       {
           if(postfix[i]=='+')
           {
            a = popnum();
            b = popnum();
            res = a + b;
            pushnum(res);
           }
           else if(postfix[i]=='-')
           {
            a = popnum();
            b = popnum();
            res = b - a;
            pushnum(res);
           }
           else if(postfix[i]=='*')
           {
            a = popnum();
            b = popnum();
            res = a * b;
            pushnum(res);
           }
           else if(postfix[i]=='/')
           {
            a = popnum();
            b = popnum();
            
            if(a==0)
            {
             printf("\n\nDivision by zero is not allowed!!!");  //exception
             flag=1;
             break;
            }
            else
            {
             res = b/a;
             pushnum(res);
            }
           }
       }
    }
    if(flag==1)
    return 0;
    
    int result = opnt->oper;
    return result;
}

void convert(char* infix,char* newinfix)   //convert the original infix expression to an expression more suitable to work with
{
        int i,j=1,len;
                
        len=strlen(infix);
        newinfix[0]='(';
        
        if(infix[0]=='-')
        {
         newinfix[1]='0';
         j=2;
        }
        for(i=0;i<strlen(infix)-1;i++)
        {
         if(infix[i]=='('&&infix[i+1]=='-')
         {
          newinfix[j]='(';
          newinfix[j+1]='0';
          j+=2;
         }
         else {
         newinfix[j]=infix[i];
         j++;
         }
        }
        
        newinfix[j]=infix[i];
        newinfix[j+1]=')';
        newinfix[j+2]='\0';
}

int CornerCases(char* newinfix)  //function to detect corner cases
    {
        int i,lcnt=0,rcnt=0;
        
            for(i=0;i<strlen(newinfix)-1;i++)
            {
               if((newinfix[i]=='+'||newinfix[i]=='-'||newinfix[i]=='*'||newinfix[i]=='/')&&(newinfix[i+1]=='+'||newinfix[i+1]=='-'||newinfix[i+1]=='*'||newinfix[i+1]=='/'))
               {
                printf("\nOperators incorrectly placed in infix notation.\n");
                return 0;
               }
            }
            
            for(i=1;i<strlen(newinfix);i++)
            {
               if(newinfix[i]==')'&&(newinfix[i-1]=='+'||newinfix[i-1]=='-'||newinfix[i-1]=='*'||newinfix[i-1]=='/'))
               {
                printf("\nHanging operator\n");
                return 0;
               }
            }
            
            for(i=0;i<strlen(newinfix)-1;i++)
            {
               if(newinfix[i]=='('&&(newinfix[i+1]=='+'||newinfix[i+1]=='*'||newinfix[i+1]=='/'))
               {
                printf("\nHanging operator\n");
                return 0;
               }
            }
            
            for(i=0;i<strlen(newinfix);i++)
            {
               if(newinfix[i]=='(')  //increment left parenthesis
               lcnt++;
               
               else if(newinfix[i]==')')
               rcnt++;   //increment right parenthesis
               
               if(lcnt<rcnt)
               {
                printf("\nParenthesis matching incorrect in infix notation.\n");
                return 0;
               }
            }
            
            if(lcnt!=rcnt)
            {
               printf("\nInequality in left-right parenthesis.\n");
               return 0;
            }
            
            for(i=0;i<strlen(newinfix)-1;i++)
               if(newinfix[i]=='('&&newinfix[i+1]==')')
               {
                printf("\nParenthesis must include something in between.\n");
                return 0;
               }
            
            for(i=1;i<strlen(newinfix);i++)
               if(newinfix[i]=='('&&isdigit(newinfix[i-1])!=0)
               {
                printf("\nLeft parenthesis cannot be immediately preceeded by a number\n");
                return 0;
               }
               
            if(newinfix[i]==')'&&isdigit(newinfix[i+1])!=0)
            {
               printf("\nRight parenthesis cannot be immediately succeeded by a number\n");
               return 0;
            }
            
            return 1;
    }

int main()  //main function
{
    int result,cc;
    char* infix = (char*)malloc(100*sizeof(char));   //memory allocation
    char* postfix = (char*)malloc(100*sizeof(char));
    char* newinfix = (char*)malloc(100*sizeof(char));
    char res;
    
    do{    
    system("CLS");
    printf("Enter the infix expression : ");
    scanf("%s",infix);
    
    convert(infix,newinfix);

    cc = CornerCases(newinfix);
    
    if(cc==1)
    {
       InfixToPostfix(newinfix,postfix);
    
       printf("\nThe postfix expression is : ");
       printf("%s",postfix);
    
       result = EvaluatePostfix(postfix);
    
       printf("\n\nThe result is : ");
       printf("%d",result);
    }
    
    printf("\n\nDo you want to try again?(y/n)...");
    res = getch();
    
    oprt = NULL;
    oprb = NULL;
    opnt = NULL;
    opnb = NULL;
    }while(res=='y'||res=='Y');
    
    free(infix);  //freeing allocated memory
    free(newinfix);
    free(postfix);
    
    return 0;
}
