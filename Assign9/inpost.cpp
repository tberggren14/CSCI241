/***************************************************************
CSCI 241         Assignment 9      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 04/01/2021
***************************************************************/

#include <string>
#include <cctype>
#include "inpost.h"
#include "mystack.h"

/********************************************************************************
 * returns postfix string
 * @param infix
 * function converts infix to postfix
 ********************************************************************************/
string convert(const string& infix){

    string postfix;     
    mystack s;
    unsigned int index = 0;

//not at the end of the infix string
    while( index < infix.length() )
    {
        if( islower(infix[index]) )    // is a lower case letter
        {
            postfix += infix[index];    //Append the current character to the postfix string 
            postfix += ' ';             //Advance to the next character of the infix string.
            index++;
        }

        else if( isdigit(infix[index]) )    // is a digit
        {
            while( isdigit(infix[index]) ){
                postfix += infix[index];        //Append the current character to the postfix string 
                index++;
            }
            postfix += ' ';
            
        }

        else if(infix[index] ==' ' )    // is a space
        {
            index++;                            //Advance to the next character of the infix string if there is a space
        }

        else if( infix[index] =='(' )    // is a left parenthesis
        {
            s.push(infix[index]);               //Push the current character onto the stack and advance to the
            index++;                            //next character of the infix string.
        }

        else if( infix[index] ==')' )    // is a right parenthesis
        {
            //the stack is not empty and the character at the top of
            //the stack is not a left parenthesis
            while(!s.empty() && s.top() != '('){
                postfix += s.top();                 //Get the top character from the stack.
                postfix += ' ';                     //Append that character to the postfix string.
                s.pop();                            // pop the stack

            }
            if(!s.empty()){
                s.pop();                            // pop the stack if stack is not empty
            }   
            index++;                                // next character
        }

        else{           // is an operator
        while(!s.empty() && precedence(s.top()) >= precedence(infix[index]))
         {
                postfix += s.top();                 //Get the top character from the stack.
                postfix += ' ';
                s.pop();                            // pop the stack
                
            }
            s.push(infix[index]);                   //Push the current character onto the stack and advance to the
            index++;                                // next character of the infix string
        }                  
    }

    while( !s.empty() )                                
    {
        postfix += s.top();                         // while stack is not empty
        postfix += ' ';                             //  get the top character and append it to the postfix
        s.pop(); 
    }

    //postfix.pop_back();
    return postfix;
}

/********************************************************************************
 * returns op
 * @param op
 * function determines what operator is being used and where to put it
 ********************************************************************************/
int precedence(char op){

    switch (op)
    {
        case '~':
        case '^':
            return 3;
            break;
        case '*':
        case '/':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
            break;
        default:
        return -1;
    }
}