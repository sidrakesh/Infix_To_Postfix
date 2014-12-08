//Siddharth Rakesh
//11CS30036

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <conio.h>

using namespace std;   //using the standard namespace

class NumberStack       //class for creating number stack
{
    public:
       NumberStack() {top = NULL;bottom = NULL;} 
       
       void push(int Number)       //push function
       {         
           node* entry = new node;
           entry->num = Number;
           entry->next = NULL;
         
           if(bottom==NULL)
           {
            top = entry;
            bottom = entry;
           }
           else
           {
            top->next = entry;
            top = entry;
           }
       }
       
       int pop()      //pop function
       {    
            int n;
            
            if(top==NULL)
            {
             cout<<"Stack empty...";
             return 0;
            }
            if(top==bottom)
            {
             n = top->num;
             top = NULL;
             bottom = NULL;
             return n;
            }
            node* t = bottom;
    
            while(t->next!=top) 
            t=t->next;
        
            n = top->num;
            top = t;
            top->next = NULL;
 
            return n;
       }
       
       int Top()      //returns top element
       {
            return top->num;
       }
       
       bool IsEmpty()   //returns whether stack is empty
       {
            if(top==NULL)
            return true;
            
            return false;
       }
       
    private:
       typedef struct tag{             //required structure for creating linked list
               int num;
               struct tag* next;
       }node;
       
       node* top;        //top and bottom pointers
       node* bottom;
};
 
class CharacterStack        //class for creating stack of operators
{
    public:
       CharacterStack() {top = NULL;bottom = NULL;}
       
       void push(char symbol)      //push function
       {         
           node* entry = new node;
           entry->oper = symbol;
           entry->next = NULL;
         
           if(bottom==NULL)
           {
            top = entry;
            bottom = entry;
           }
           else
           {
            top->next = entry;
            top = entry;
           }
       }
       
       char pop()    //pop function
       {    
            char ch;
            
            if(top==NULL)
            {
             cout<<"Stack empty...";
             return NULL;
            }
            if(top==bottom)
            {
             ch = top->oper;
             top = NULL;
             bottom = NULL;
             return ch;
            }
            node* t = bottom;
    
            while(t->next!=top) 
            t=t->next;
        
            ch = top->oper;
            top = t;
            top->next = NULL;
 
            return ch;
       }
       
       char Top()      //returns top element
       {
            return top->oper;
       }
       
       bool IsEmpty()   //returns whether stack is empty
       {
            if(top==NULL)
            return true;
            
            return false;
       }
       
    private:
       typedef struct tag{        //required struct for character stack
               char oper;
               struct tag* next;
       }node;
       
       node* top;    //top and bottom pointers
       node* bottom;
};

string InfixToPostfix(string infix)    //function for converting infix to postfix
{
    int i;
    string postfix;
    char c;
    CharacterStack Stack;
    
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
          Stack.push('(');
          
          else if(infix[i]=='+'||infix[i]=='-')
          {
              while(Stack.IsEmpty()==false&&Stack.Top()!='(')
              {
                 c=Stack.pop();
                 postfix.push_back(c);
              }
              Stack.push(infix[i]);
          }
          else if((infix[i]=='*'||infix[i]=='/')&&Stack.IsEmpty()==false&&(Stack.Top()=='*'||Stack.Top()=='/'))
          {
              while(Stack.IsEmpty()==false&&(Stack.Top()=='*'||Stack.Top()=='/'))
              {
                 c=Stack.pop();
                 postfix.push_back(c);
              }
              Stack.push(infix[i]);
          }
          else if(infix[i]!=')')
          { 
              Stack.push(infix[i]);
          }
          else
          {
             while(Stack.IsEmpty()==false)
             {
                 c = Stack.pop();
                 if(c=='(')
                   break;
             
                 else
                  postfix.push_back(c);
             } 
          }
       }
       
    }
    
    while(Stack.IsEmpty()==false)
    {
       c = Stack.pop();
       postfix.push_back(c);
    }
    
    return postfix;
}

int EvaluatePostfix(string postfix)        //function to evaluate postfix
{
    NumberStack Stack;
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
           Stack.push(atoi(numb));
       }
       
       else
       {
           if(postfix[i]=='+')
           {
            a = Stack.pop();
            b = Stack.pop();
            res = a + b;
            Stack.push(res);
           }
           else if(postfix[i]=='-')
           {
            a = Stack.pop();
            b = Stack.pop();
            res = b - a;
            Stack.push(res);
           }
           else if(postfix[i]=='*')
           {
            a = Stack.pop();
            b = Stack.pop();
            res = a * b;
            Stack.push(res);
           }
           else if(postfix[i]=='/')
           {
            a = Stack.pop();
            b = Stack.pop();
            
            try
            {
                if(a==0)
                   throw 1;
                
                res = b/a;
                Stack.push(res);
            }
            catch(int k)
            {
                cout<<"\n\nDivision by zero is not allowed!!!";
                return NULL;
            }
           }
       }
    }
    
    int result = Stack.Top();
    return result;
}

bool CheckExceptions(string infix)     //function for cheacking exceptions
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
           
           if(lcnt<rcnt)     //left parenthesis less than right parenthesis
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
        cout<<"\nHanging operator\n";
        
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
        cout<<"\nHanging operator.\n";
        
        return false;
    }
}

int main()    //main function
{
    string infix,postfix;
    int i,result;
    char res;
    bool IsCorrect;
    
    do{
    system("CLS");
    cout<<"Enter the infix expression : ";
    cin>>infix;
    
    infix.insert(0,"(");          //making infix more usable
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
