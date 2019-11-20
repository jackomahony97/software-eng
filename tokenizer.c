//
// Created by jacko on 20/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"

void tokenizer() {
    FILE *infile, *outfile;
    infile = fopen("../temp/input.txt", "r");
    outfile = fopen("../temp/tokenizer.txt", "w");
    char line[1024];

    fgets(line, 1024, infile); // reads in first line fom input file
    for (int i = 0; line[i]; i++) {
        if (line[i] == '+'
            || line[i] == '-'
            || line[i] == '/'
            || line[i] == '*'
            || line[i] == '%'
            || line[i] == '^'
            || line[i] == '('
            || line[i] == ')'
            || line[i] == '\n'
            || line[i] == '\r'
                ) {
            char c = '\n';
            fprintf(outfile,"%c ",c);
            fprintf(outfile,"%c ",line[i]);
            fprintf(outfile,"%c ",c);
        } else if ((isdigit(line[i])) || (line[i] == '.')) {
            fprintf(outfile,"%c ",line[i]);
        }
    }
    fclose(infile);
    fclose(outfile);
}