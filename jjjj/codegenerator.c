/*
Code Generator
Author: Kevin O' Donovan
The Code Generator program takes the output file from the infix2postfix program as input.
It will then convert each token into an instruction, which will be outputted in an "instructions" file.
The HLT(Halt) instruction will be appended to the end of the output file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "codegenerator.h"

void codegenerator() {  /* This file comprises of 1 function which translates the input file into a single output file */

    FILE *infile, *outfile;  /* Initialise input and output files */
    char c[100];  /* Declare maximum token size */
    int result;  /* Initialise integer to hold result of string comparisons */
    char loadnum[100] = "LOADNUM, ";  /* Initialise string for LOADNUM instructions */

    infile = fopen("./temp/postfix.txt", "r");  /* Open input file, create if non-existent */
    outfile = fopen("./temp/instructions.txt", "w+");  /* Open output file, create if non-existant */

    if (infile == NULL) {
        printf("ERROR: Unable To Access Postfix File\n");
        exit(1);  /* If unable to access the output of infix2postfix, the program will exit and an error will display. */
    }

    while (fgets(c, sizeof c, infile) != NULL) {
        strtok(c, "\n");  /* Strip the newline character from each token - newline character will not be removed if it is the only character in that line. */

        result = strcmp(c, "+");
        if (result == 0) {
            fputs("ADD,\n", outfile);  /* Compare with '+' operator. If true, print 'ADD' instruction. */
        } else {
            result = strcmp(c, "-");
            if (result == 0) {
                fputs("SUB,\n", outfile);  /* Compare with '-' operator. If true, print 'SUB' instruction. */
            } else {
                result = strcmp(c, "*");
                if (result == 0) {
                    fputs("MUL,\n", outfile);  /* Compare with '*' operator. If true, print 'MUL' instruction. */
                } else {
                    result = strcmp(c, "/");
                    if (result == 0) {
                        fputs("DIV,\n", outfile);  /* Compare with '/' operator. If true, print 'DIV' instruction. */
                    } else {
                        result = strcmp(c, "^");
                        if (result == 0) {
                            fputs("EXP,\n", outfile);  /* Compare with '^' operator. If true, print 'EXP' instruction. */
                        } else {
                            result = strcmp(c, "%");
                            if (result == 0) {
                                fputs("MOD,\n", outfile);  /* Compare with '%' operator. If true, print 'MOD' instruction. */
                            } else {
                                result = strcmp(c, "\n");
                                if (result == 0) {
                                    fputs("", outfile);  /* Compare with newline character. If true, print empty string. */
                                } else {
                                    result = strcmp(c, "");
                                    if (result == 0) {
                                        fputs("", outfile);  /* Compare with empty string. If true, print empty string. */
                                    } else {
                                        strcat(loadnum, c);  /* Concatenate token to loadnum string. */
                                        strcat(loadnum, ",\n");  /* Concatenate newline character to loadnum string. */
                                        fputs(loadnum, outfile);  /* Print LOADNUM instruction to outfile. */
                                        strcpy(loadnum, "LOADNUM ");  /* Reset loadnum string to initial value . */
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }

    fputs("HLT,", outfile);  /* Append Halt instruction to the end of the program */

    fclose(infile);  /* Close input file */
    fclose(outfile);  /* Close output file */
}

