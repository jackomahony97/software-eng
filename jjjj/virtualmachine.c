//
// Created by jacko on 20/11/2019.
//


/**
* The Virtual Machine program reads an input file of instructions and executes them using a stack and writes the amswer to an output file
* @author Jack O Mahony (117498152)
* @date 13/11/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "virtualmachine.h"

#define STACK_MAX 256 /** Max size of stack (overflow) */

#define INPUT_FILE "./temp/instructions.txt" /** Location of file */
#define OUTPUT_FILE "./temp/solutions.txt" /** Location of file */


int running = 1; /** Keep track of whether HLT(end of instructions) is reached */

int ip = 0; /** Instruction Pointer */
int sp = -1; /** Stack pointer */

float program[STACK_MAX]; /** Array containing instructions */

float stack[STACK_MAX]; /** Stack */

typedef enum {
    ADD, /** Addition = 0*/
    SUB, /** Subtraction = 1 */
    MUL, /** Multiplication = 2 */
    DIV, /** Division = 3 */
    EXP, /** Exponent = 4 */
    MOD, /** Modulus = 5 */
    LOADNUM, /** Push = 6 */
    HLT  /** Halt = 7 */
} InstructionSet;

int checker(const char input[]){
    /**
     * checker matches a string to its instruction enum equivalent
     * @param input[] constant char array instruction
     * @return result Integer instruction enum equivalent
     */
    int result = 0; /** instruction enum to be returned */
    if(strcmp(input, "ADD")==0){
        /** Addition = 0*/
        result = 0;
    }
    else if(strcmp(input, "SUB")==0){
        /** Subtraction = 1 */
        result = 1;
    }
    else if(strcmp(input, "MUL")==0){
        /** Multiplication = 2 */
        result = 2;
    }
    else if(strcmp(input, "DIV")==0){
        /** Division = 3 */
        result = 3;
    }
    else if(strcmp(input, "EXP")==0){
        /** Exponent = 4 */
        result = 4;
    }
    else if(strcmp(input, "MOD")==0){
        /** Modulus = 5 */
        result = 5;
    }
    else if(strcmp(input, "LOADNUM")==0){
        /** Push = 6 */
        result = 6;
    }
    else if(strcmp(input, "HLT")==0){
        /** Halt = 7 */
        result = 7;
    }
    return result;
}

void write2file(float res) {
    /**
    * eval writes a parameter res to a file
    * @param res Integer the value to be written to file
    */
    char filename[] = OUTPUT_FILE; /** Location of file */
    FILE *file = fopen ( filename, "w+" ); /** Open file */
    if (res-(int)res == 0) { /** Check if integer */
        fprintf(file, "%d\n", (int)res); /** Write to file (integer)*/
    } else {
        fprintf(file, "%f\n", res); /** Write to file (float*/
    }
    fclose(file); /** Close file */
}

void eval(int instr) {
    /**
     * eval executes a parameter instr via the stack
     * @param instr Integer the type of instruction
     */
    switch (instr) {
        case HLT: {
            float val_popped = stack[sp--]; /** Pop top of stack */
            /** printf("%d\n", val_popped);  Print answer */
            write2file(val_popped);
            running = 0; /** End loop */
            break;
        }
        case LOADNUM: {
            sp++; /** Increment stack pointer */
            ip++; /** Increment instruction pointer */
            stack[sp] = program[ip];  /** Push to top of stack */
            break;
        }
        case ADD: {
            float a = stack[sp--]; /** Pop top of stack */
            float b = stack[sp--]; /** Pop top of stack */
            float result = a + b; /** Implement instruction */
            sp++; /** Increment stack pointer */
            stack[sp] = result; /** Result goes to top of stack */
            break;
        }
        case SUB: {
            float a = stack[sp--]; /** Pop top of stack */
            float b = stack[sp--]; /** Pop top of stack */
            float result = b - a; /** Implement instruction */
            sp++; /** Increment stack pointer */
            stack[sp] = result; /** Result goes to top of stack */
            break;
        }
        case MUL: {
            float a = stack[sp--]; /** Pop top of stack */
            float b = stack[sp--]; /** Pop top of stack */
            float result = b * a; /** Implement instruction */
            sp++; /** Increment stack pointer */
            stack[sp] = result; /** Result goes to top of stack */
            break;
        }
        case DIV: {
            float a = stack[sp--]; /** Pop top of stack */
            float b = stack[sp--]; /** Pop top of stack */
            float result = b / a; /** Implement instruction */
            sp++; /** Increment stack pointer */
            stack[sp] = result; /** Result goes to top of stack */
            break;
        }
        case MOD: {
            float a = stack[sp--]; /** Pop top of stack */
            float b = stack[sp--]; /** Pop top of stack */
            float result = remainder(a, b);
	    result = result * -1; /** Implement instruction */
            sp++; /** Increment stack pointer */
            stack[sp] = result; /** Result goes to top of stack */
            break;
        }
        case EXP: {
            float a = stack[sp--]; /** Pop top of stack */
            float b = stack[sp--]; /** Pop top of stack */
            float result = pow(b, a); /** Implement instruction */
            sp++; /** Increment stack pointer */
            stack[sp] = result; /** Result goes to top of stack */
            break;
        }
    }
}

int virtualmachine() {
    /**
    * Main function which reads input from file, seperate into lines and sublines and call eval with each instruction
    * @return 0 Integer
    */
    char filename[] = INPUT_FILE; /** Location of file */
    FILE *file = fopen ( filename, "r" ); /** Open file */

    if (file != NULL) { /** Check file is not empty */
        char line [50]; /** Max line length */
        int i = 0; /** Counter for index in array program */
        while(fgets(line,sizeof (line),file)!= NULL && running == 1)  { /** Run through each line */
            char *substr = NULL; /** Substring */
            substr = strtok(line,", "); /** Deliminator  ", " */
            while(substr!= NULL){ /** Iterate through substring */
                if (strcmp(substr, "\n")) { /** Check if empty */
                    if (isdigit(*substr) == 0) { /** If its a digit */
                        program[i] = checker(substr); /** Add instruction to array program */
                        i++; /** Increment counter for index in array program */
                    } else { /** Not a digit */

                        program[i] = atof(substr); /** Convert to instruction enum */
                        i++; /** Increment counter for index in array program */
                    }
                }
                substr = strtok(NULL, ", "); /** Next line */
            }
            eval(program[ip]); /** Call eval on every iteration with instruction */
            ip++; /** Increment the instruction pointer */
        }
        fclose(file); /** Close file */
    }
    else {
        perror(filename); /** If file name is not correct */
    }
    return 0;
}
