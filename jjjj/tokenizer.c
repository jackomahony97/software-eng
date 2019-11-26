/**
* The Tokenizer program reads an input file with one calculation on the first line,
* checks the calculation for syntax errors and then prints the calculation to a new
* file with one 'token' (integer, float, bracket or operator) per line.
* @author Mark O'Gorman (117333271)
* @date 13/11/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



bool checkBrackets(char line[]){ // checks that the calculation has an equal number of ( and ) symbols
    int openBrackets = 0;
    int closeBrackets = 0;
    for(int i = 0; line[i]; i++){
        if (line[i] == '('){
            openBrackets += 1;
        }
        if (line[i] == ')'){
            closeBrackets += 1;
        }
    }
    if (openBrackets == closeBrackets){
       return true;
    }
    else{
        return false;
    }
}

bool checkDecimals(char line[]){ // checks that there is not more than one decimal place in a given float
    int decimalCount = 0;
    for(int i = 0; line[i]; i++){
        if (line[i] == '.') { // this indicates that we are inside a float
            decimalCount += 1;
            if (decimalCount >= 2){ // if there are more than one decimals, return false
                return false;
            }
        }
        else {
		if (!isdigit(line[i])){ // once we have reached the end of the float, reset the counter
            		decimalCount = 0;
        	}
	}
    }
    return true;
}

bool checkOperators(char line[]){ // check that there are no syntax errors caused by adjacent or trailing operator symbols

    if (line[0]== '*'
        ||line[0]=='/'
        || line[0] == '%'
        || line[0] == '^'){
            return false;
    }
    for(int i = 0; line[i]; i++){
        if (line[i] == '+' // if there is an operator symbol..
            || line[i] == '-'
            || line[i] == '/'
            || line[i] == '*'
            || line[i] == '^'
            || line[i] == '%'){
            if (!(line[i+1] == '(' // if the operator is not adjacent to a token it can operate on, throw an error
                || line[i+1] == ')'
                || isdigit(line[i+1]))
                ){
                return false;
            }
        }
    }
    return true;
}

void removeIllegalChars(char line[]){ // removes characters that the program must ignore, so that they will not interfere with other syntax checks.
    int count = 0; // count characters not being kept
    for (int i = 0; line[i]; i++){
        if (line[i] == '+'    // these are the legal characters that will be allowed
            || line[i] == '-'
            || line[i] == '/'
            || line[i] == '*'
            || line[i] == '('
            || line[i] == ')'
            || line[i] == '%'
            || line[i] == '^'
            || line[i] == '\n'
            || line[i] == '\r'
            || isdigit(line[i])
            || line[i] == '.'
            ){
            line[count++] = line[i];
        }
    }
    line[count] = '\0'; // end of line char placed at end of string to be kept
}

void printTokensToNewLine(char line[], FILE *outfile){ // prints one token (integer, float, operator or bracket) to a new line each of an output file
    for(int i = 0; line[i]; i++){
            char newline = '\n';
            if (line[i] == '+'
                || line[i] == '-'
                || line[i] == '/'
                || line[i] == '*'
                || line[i] == '('
                || line[i] == ')'
                || line[i] == '%'
                || line[i] == '^'
                )
                {
                    fputc(line[i], outfile);
                    fputc(newline, outfile);
            }
            else if ( (isdigit(line[i])) || (line[i] == '.') ) {
				fputc(line[i], outfile);
                if (!(line[i+1] == '.'|| isdigit(line[i+1]))){
                    fputc(newline, outfile);
                }
            }
        }
}

bool checkSyntax(char line[]){ // runs checks for operators, brackets and decimal place syntax
    if (checkOperators(line)
        &&checkBrackets(line)
        &&checkDecimals(line)
        )
        {
        return true;

    }
    else{
        return false;
    }

}


void append(char subject[], const char insert[], int pos) {// appends the string insert[] into subject[] at position pos
    char buf[100] = {};

    strncpy(buf, subject, pos);
    int len = strlen(buf);
    strcpy(buf+len, insert);
    len += strlen(insert);
    strcpy(buf+len, subject+pos);
    strcpy(subject, buf);
}

void fixDecimals(char line[]){
    char str[] = "0";
    for(int i = 0; line[i]; i++){
        if (line[i] == '.'){

            if(!(isdigit(line[i+1]))){
                append(line, str, i+1);
            }
            if (i == 0
                ||(!isdigit(line[i-1]))
                ){
                append(line, str, i);
            }
        }
    }
}
void fixFirstOperators(char line[]){ // fixes the case "-200+100" where the first operator in a line indicates the sign of the integer, rather than a function
    char str[] = "0";
    if ((line[0] == '+')||(line[0] == '-')){
            append(line, str, 0);
        }
    }

void fixBracketMultiplication(char line[]){// inserts '*' between brackets so that they are multiplied appropriately in the code generator
    char str[] = "*";
    for(int i = 0; line[i]; i++){
        if( (line[i] == ')') && ((line[i+1] == '(') || (isdigit(line[i+1])))){
                append(line, str, i+1);
        }
        if( (line[i] == '(') && ((isdigit(line[i-1])))){
                append(line, str, i);
        }
    }
}

int tokenizer(){ // function called by main in order to execute the tokeniser program
    FILE *infile, *outfile;
    infile = fopen("./temp/input.txt","r");
    outfile = fopen("./temp/tokenizer.txt", "w+");
    char line[1024];
    fgets( line ,1024, infile); // reads in first line from input file

    removeIllegalChars(line);
    fixFirstOperators(line);
    fixDecimals(line);
    fixBracketMultiplication(line);

    if (checkSyntax(line)){ // counts the number of ( and ) symbols and returns syntax error if they are unequal.
        printTokensToNewLine(line, outfile);
        fclose(infile);
        fclose(outfile);
        return 0;
    }
    else {
        fputs("syntax error", outfile);
        fclose(infile);
        fclose(outfile);
        return 1;
    }
}
