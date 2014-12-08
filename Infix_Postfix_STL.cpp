//Siddharth Rakesh
//11CS30036

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <conio.h>
#include <stack>         //using the standard template library for implementing stack

using namespace std;

string InfixToPostfix(string infix)       //function to convert infix to postfix
{
    int i;
    string postfix;
    char c;
    stack<char>CStack;   //using STL stack
    
    for(i=0;i<infix.length();i++)
    {
       if(isdigit(infix[i])!=0)
       {
          postfix.push_back(infix[i]);
          
          if(infix[i+1]=='+'||infix[i+1]=='-'||infix[i+1]=='*'||infix[i+1]=='/')
          {
             postfix.push_back(' ');
          }
       }
       else
       {
          if(infix[i]=='(')
          CStack.push('(');
          
          else if(infix[i]=='+'||infix[i]=='-')
          {
              while(CStack.empty()==false&&CStack.top()!='(')
              {
                 postfix.push_back(CStack.top());
                 CStack.pop();
              }
              CStack.push(infix[i]);
          }
          else if((infix[i]=='*'||infix[i]=='/')&&CStack.empty()==false&&(CStack.top()=='*'||CStack.top()=='/'))
          {
              while(CStack.empty()==false&&(CStack.top()=='*'||CStack.top()=='/'))
              {
                 postfix.push_back(CStack.top());
                 CStack.pop();
              }
              CStack.push(infix[i]);
          }
          else if(infix[i]!=')')
          { 
              CStack.push(infix[i]);
          }
          else
          {
             while(CStack.empty()==false)
             {
                 c = CStack.top();
                 CStack.pop();
                 if(c=='(')
                   break;
             
                 else
                  postfix.push_back(c);
             } 
          }
       }
       
    }
    
    while(CStack.empty()==false)
    {
       postfix.push_back(CStack.top());
       CStack.pop();
       
    }
    
    return postfix;
}

int EvaluatePostfix(string postfix)    //function to evaluate postfix
{
    stack<int>NStack;    //using STL stack
    char numb[5];
    int i,j,a,b,res;

    for(i=0;i<postfix.length();i++)
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
           NStack.push(atoi(numb));
       }
       
       else
       {
           if(postfix[i]=='+')
           {
            a = NStack.top();
            NStack.pop();
            b = NStack.top();
            NStack.pop();
            res = a + b;
            NStack.push(res);
           }
           else if(postfix[i]=='-')
           {
            a = NStack.top();
            NStack.pop();
            b = NStack.top();
            NStack.pop();
            res = b - a;
            NStack.push(res);
           }
           else if(postfix[i]=='*')
           {
            a = NStack.top();
            NStack.pop();
            b = NStack.top();
            NStack.pop();
            res = a * b;
            NStack.push(res);
           }
           else if(postfix[i]=='/')
           {
            a = NStack.top();
            NStack.pop();
            b = NStack.top();
            NStack.pop();
            
            try
            {
                if(a==0)
                   throw 1;
                
                res = b/a;
                NStack.push(res);
            }
            catch(int k)
            {
                cout<<"\n\nDivision by zero is not allowed!!!";
                return NULL;
            }
           }
       }
    }
    
    int result = NStack.top();
    return result;
}

bool CheckExceptions(string infix)     //function to check for exceptions
{
    int i,lcnt=0,rcnt=0;

    try
    {
        for(i=0;i<infix.length()-1;i++)
        {
           if((infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/')&&(infix[i+1]=='+'||infix[i+1]=='-'||infix[i+1]=='*'||infix[i+1]=='/'))
           throw 1;
        }
        
        for(i=1;i<infix.length();i++)
           if(infix[i]==')'&&(infix[i-1]=='+'||infix[i-1]=='-'||infix[i-1]=='*'||infix[i-1]=='/'))
               throw 2;
        
        for(i=0;i<infix.length();i++)
        {
           if(infix[i]=='(')
           lcnt++;
           
           else if(infix[i]==')')
           rcnt++;
           
           if(lcnt<rcnt)
           throw 3;
        }
        
        if(lcnt!=rcnt)
           throw 4;
        
        for(i=0;i<infix.length()-1;i++)
           if(infix[i]=='('&&infix[i+1]==')')
              throw 5;
        
        for(i=1;i<infix.length()-1;i++)
           if(infix[i]=='('&&isdigit(infix[i-1])!=0)
              throw 6;
           
           if(infix[i]==')'&&isdigit(infix[i+1])!=0)
              throw 7;
        
        for(i=0;i<infix.length()-1;i++)
           if(infix[i]=='('&&(infix[i+1]=='+'||infix[i+1]=='*'||infix[i+1]=='/'))
               throw 8;
        
        return true;
    }
    catch(int k)
    {
        if(k==1)
        cout<<"\nOperators incorrectly placed in infix notation.\n";
        
        else if(k==2)
        cout<<"\nHanging operator at the front or end\n";
        
        else if(k==3)
        cout<<"\nParenthesis matching incorrect in infix notation.\n";
        
        else if(k==4)
        cout<<"\nInequality in left-right parenthesis.\n";
        
        else if(k==5)
        cout<<"\nParenthesis must include something in between.\n";
                
        else if(k==6)
        cout<<"\nLeft parenthesis cannot be immediately preceeded by a number\n";
        
        else if(k==7)
        cout<<"\nRight parenthesis cannot be immediately succeeded by a number\n";
        
        else if(k==8)
        cout<<"\nHangin operator.\n";
        
        return false;
    }
}

int main()      //main function
{
    string infix,postfix;
    int i,result;
    char res;
    bool IsCorrect;
    
    do{
    system("CLS");
    cout<<"Enter the infix expression : ";
    cin>>infix;
    
    infix.insert(0,"(");     //making infix more usable
    infix.append(")");
    
    for(i=0;i<infix.length()-1;i++)
    if(infix[i]=='('&&infix[i+1]=='-')
    {
     infix.insert(i+1,"0");
    }
    
    IsCorrect = CheckExceptions(infix);

    if(IsCorrect==true)
    {
        postfix = InfixToPostfix(infix);
    
        cout<<"\nThe postfix expression is : ";
        cout<<postfix;
    
        result = EvaluatePostfix(postfix);
    
        cout<<"\n\nThe result is : "<<result;
    }
    
    cout<<"\n\nDo you want to try again?(y/n)...";
    res = getch();
    
    }while(res=='y'||res=='Y');
    
    return 0;
}
