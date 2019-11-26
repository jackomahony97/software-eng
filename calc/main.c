/**
* Main acts as an interface to all the components of the calculator
* @author everyone
* @date 26/11/2019
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
    /**
    * Main function which reads input from file and writes solution to solution_file.txt
    * @return 0 Integer
    */
    char path[100]; /** file path */
    char line[1024]; /** line buffer */
    int result;
    FILE *infile, *outfile; 

    mkdir("./temp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); /** make a directory */
    printf( "Enter a path :"); 
    scanf("%s", path); /** get file path from user (testing ../example.txt) */
    infile = fopen(path,"r"); /** open input file (read only) */

    while(fgets(line,sizeof (line),infile)!= NULL)  { /** for each line in input file */
	
        outfile = fopen("./temp/input.txt", "w+"); /** open output file (write only) */
        fprintf(outfile, "%s\n", line); /** write line to output file  */
        fclose(outfile); /** close output file */
        result = tokenizer(); /** call tokenizer() */
	if (result == 0) {
        	result = infix2postfix(); /** call infix2postfix() */
	}
	else {
		printf("Error in Tokenizer file.");
		break;
		}
	if (result == 0) {
		result = codegenerator(); /** call codegenerator */
			}
	else {
		printf("Error in Infix2postfix file.");
		break;
		}
	if (result == 0) {
		result = virtualmachine(); /** call virtualmachine */
			}
	else {
		printf("Error in Code Generator file.");
		break;
		}
	if(result==0) {
		printf("Calculated. Please check result in: ./temp/solutions.txt. \n");
			}
	else {
		printf("Error in Virtual Machine file.");
		break;
		}
			
    }
    fclose(infile); /** close input file */
    return 0;
}
