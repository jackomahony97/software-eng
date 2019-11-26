/**
* The tokeniser reads in a line of calculation, removes invalid characters ans checks for syntax errors, before printing to an output file.
* @author Mark O'Gorman
* @date 13/11/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool checkBrackets(char line[]){// check syntax for brackets
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
    if (openBrackets == closeBrackets){//check syntax for brackets
       return true;
    }
    else{
        return false;
    }
}

bool checkDecimals(char line[]){//check syntax for decimal places
    int decimalCount = 0;
    for(int i = 0; line[i]; i++){
        if (line[i] == '.') {
            decimalCount += 1;
            if (decimalCount >= 2){
                return false;
            }
        }
        else {
		if (!isdigit(line[i])){
            		decimalCount = 0;
        	}
	}
    }
    return true;
}

bool checkOperators(char line[]){// check syntax for operators

    for(int i = 0; line[i]; i++){
        if (line[i] == '+'
            || line[i] == '-'
            || line[i] == '/'
            || line[i] == '*'
            || line[i] == '^'
            || line[i] == '%'){
            if (!(line[i+1] == '('
                || line[i+1] == ')'
                || isdigit(line[i+1]))
                ){
                return false;
            }
        }
    }
    return true;
}

int removeIllegalChars(char line[]){
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
return 0;
}

void printTokensToNewLine(char line[], FILE *outfile){ // prints to the output file, splitting the string onto tokens on one new line per token
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

bool checkSyntax(char line[]){ // calls functions to check operator, bracket and decimal place syntax
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

// inserts into subject[] at position pos
void append(char subject[], const char insert[], int pos) {
    char buf[100] = {}; // 100 so that it's big enough. fill with 0
    // or you could use malloc() to allocate sufficient space

    strncpy(buf, subject, pos); // copy at most first pos characters
    int len = strlen(buf);
    strcpy(buf+len, insert); // copy all of insert[] at the end
    len += strlen(insert);  // increase the length by length of insert[]
    strcpy(buf+len, subject+pos); // copy the rest

    strcpy(subject, buf);   // copy it back to subject
    // deallocate buf[] here, if used malloc()
}

int fixDecimals(char line[]){// fixes the cases "123." to "123.0" and ".123" to "0.123"
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
	return 0;
}
int fixFirstOperators(char line[]){ // fixes the case "-200+100" where the first operator in a line indicates the sign of the integer, rather than a function
    char str[] = "0";
    if ((line[0] == '+')||(line[0] == '-')){
            append(line, str, 0);
        }
	return 0;
    }

int fixBracketMultiplication(char line[]){
    char str[] = "*";
    for(int i = 0; line[i]; i++){
        if( (line[i] == ')') && ((line[i+1] == '(') || (isdigit(line[i+1])))){
                append(line, str, i+1);
        }
        if( (line[i] == '(') && ((isdigit(line[i-1])))){
                append(line, str, i);
        }
    }
return 0;
}

int tokenizer(){
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
