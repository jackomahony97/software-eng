/**
* The infix2postfix program reads an input file of tokenizer and convert them to postfix format using a stack and writes the result to an postfix file.
* @author Hoang Anh Mai (117101156)
* @date 25/11/2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "infix2postfix.h"

#define STKSZ 100

//Init a struct for stack
struct stack { char items[STKSZ]; int top;} stk;

//Function to push element to the stack if the stack is full and push() is called print out overflow error.
void push(char ele)
{
    if (stk.top + 1 == STKSZ) {
        printf("\n Stack Overflow!\n");
        exit(1);
    }
    stk.items[++stk.top] = ele;
}

//Function to pop element to the stack if there is no element left and pop() is called print out underflow error.
char pop()
{
    if (stk.top == -1) {
        printf("\n Stack Underflow!\n");
        exit(1);
    }
    return (stk.items[stk.top--]);
}

//Set priority for operators in the stack.
int priority(char c)
{
    switch (c)
    {
        case '(': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '$': return 3;
    }
}

//Main function.
int infix2postfix(void)
{
    stk.top=-1;
    FILE *infile,*outfile;
    char expr[60],*e, x,c;
    infile = fopen("./temp/tokenizer.txt","r");
    outfile= fopen("./temp/postfix.txt","w+");
// If infile is available loop through each character in the file and convert the file to postfix. Return 1 if no error.    
    if (infile) {
        while ((c = getc(infile)) != EOF) {
            if ( (isalnum(c)) || (c == '.') ) {
                fprintf(outfile,"%c", c);
            }
            else if (c == '\n' || c == ' ') {}
            else if (c == ')') {
                while ( (x = pop()) != '(')
                    fprintf(outfile,"\n%c", x);
            }
            else if (c == '(') {
                fprintf(outfile,"\n");
                push(c);
            }
            else {
                fprintf(outfile,"\n");
                while ( priority(stk.items[stk.top]) >= priority(c) ) fprintf(outfile,"%c\n", pop());
                push(c);
            }
        }
        while (stk.top>-1) {fprintf(outfile,"\n%c", pop());}
        return 1;
    }
    fclose(infile);
    fclose(outfile);
//Else return 0.
    return 0;
}
