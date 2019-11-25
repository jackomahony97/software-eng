#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool checkBrackets(char line[]){
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

bool checkOperators(char line[]){
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

void removeIllegalChars(char line[]){
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

void printTokensToNewLine(char line[], FILE *outfile){
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

bool checkSyntax(char line[]){
    if (checkOperators(line)
        &&checkBrackets(line)
        )
        {
        return true;

    }
    else{
        return false;
    }

}




main(){
    FILE *infile, *outfile;
    infile = fopen("input.txt","r");
    outfile = fopen("postfix.txt", "w+");
    char line[1024];
    fgets( line ,1024, infile); // reads in first line from input file
    removeIllegalChars(line);

    if (checkSyntax(line)){ // counts the number of ( and ) symbols and returns syntax error if they are unequal.
        printTokensToNewLine(line, outfile);
    }
    else {
        fputs("syntax error", outfile);
    }
}
