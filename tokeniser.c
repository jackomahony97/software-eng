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




main()
{
    FILE *infile, *outfile;
    infile = fopen("input.txt","r");
    outfile = fopen("postfix.txt", "w+");
    char line[1024];
    fgets( line ,1024, infile); // reads in first line from input file
    if (checkSyntax(line)){ // counts the number of ( and ) symbols and returns syntax error if they are unequal.

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
                || line[i] == '\n'
                || line[i] == '\r'
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

    else {
        fputs("syntax error", outfile);
    }
    exit;
}
