//
// Created by jacko on 20/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "infix2postfix.h"

#define STKSZ 100

struct stack { char items[STKSZ]; int top;} stk;

void push(char ele)
{
    if (stk.top + 1 == STKSZ) {
        printf("\n[E] Stack Overflow!\n");
        exit(1);
    }
    stk.items[++stk.top] = ele;
}

char pop()
{
    if (stk.top == -1) {
        printf("\n[E] Stack Underflow!\n");
        exit(1);
    }
    return (stk.items[stk.top--]);
}


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

int infix2postfix(void)
{
    stk.top=-1;
    FILE *infile,*outfile;
    char expr[60],*e, x,c;
    infile = fopen("../temp/tokenizer.txt","r");
    outfile= fopen("../temp/postfix.txt","w");
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
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}
