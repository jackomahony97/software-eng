
//
// Created by jacko on 20/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegenerator.h"

void codegenerator() {

    FILE *infile, *outfile;
    char c[100]; /* or other suitable maximum line size */
    int result;
    char loadnum[100] = "LOADNUM, ";

    infile = fopen("./temp/postfix.txt", "r");
    outfile = fopen("./temp/instructions.txt", "w+");

    if (infile == NULL) {
        printf("ERROR: Unable To Access Postfix File\n");
        exit(1);
    }

    while (fgets(c, sizeof c, infile) != NULL) {
        strtok(c, "\n");

        result = strcmp(c, "+");
        if (result == 0) {
            fputs("ADD,\n", outfile);
        } else {
            result = strcmp(c, "-");
            if (result == 0) {
                fputs("SUB,\n", outfile);
            } else {
                result = strcmp(c, "*");
                if (result == 0) {
                    fputs("MUL,\n", outfile);
                } else {
                    result = strcmp(c, "/");
                    if (result == 0) {
                        fputs("DIV,\n", outfile);
                    } else {
                        result = strcmp(c, "^");
                        if (result == 0) {
                            fputs("EXP,\n", outfile);
                        } else {
                            result = strcmp(c, "%");
                            if (result == 0) {
                                fputs("MOD,\n", outfile);
                            } else {
                                result = strcmp(c, "\n");
                                if (result == 0) {
                                    fputs("", outfile);
                                } else {
                                    result = strcmp(c, "");
                                    if (result == 0) {
                                        fputs("", outfile);
                                    } else {
                                        strcat(loadnum, c);
                                        strcat(loadnum, ",\n");
                                        fputs(loadnum, outfile);
                                        strcpy(loadnum, "LOADNUM, ");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }

    fputs("HLT,", outfile);

    fclose(infile);
    fclose(outfile);
}
