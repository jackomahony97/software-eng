/**
* Main acts as an intrface to all the components of the calculator
* @author Jack O Mahony (117498152)
* @date 13/11/2019
*/

#include <stdio.h>
#include "virtualmachine.h"
#include "tokenizer.h"
#include "codegenerator.h"
#include "infix2postfix.h"
#include <string.h>
#include <sys/stat.h>

int main( )
{
    char path[100];
    char line[1024];
    FILE *infile, *outfile;

    mkdir("../temp"); //make a directory
    printf( "Enter a path :");
    scanf("%s", path); // needs to be ../example.txt
    infile = fopen(path,"r");

    while(fgets(line,sizeof (line),infile)!= NULL)  {
        outfile = fopen("../temp/input.txt", "w");
        fprintf(outfile, "%s\n", line);
        fclose(outfile);
        tokenizer();
        infix2postfix();
        codegenerator();
        virtualmachine();
        remove("../temp/input.txt");
        remove("../temp/tokenizer.txt");
        remove("../temp/postfix.txt");
        remove("../temp/instructions.txt");
    }
    fclose(infile);
    return 0;
}
