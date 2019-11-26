#include <ctap.h>
#include "infix2postfix.c"
#include "virtualmachine.c"
#include "math.h"
#include "tokenizer.c"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



TESTS {
	//tokenizer (syntax checks)
	ok(checkBrackets("1+2") == true, "correct brackets");
	ok(checkBrackets("(1+2") == false, "Missing right bracket");
	ok(checkBrackets("(1+2") == false, "Missing left bracket");
	ok(checkBrackets("1+2") == true, "no brackets");

	ok(checkDecimals("1.1") == true, "correct decimals");
	ok(checkDecimals("1.1.1") == false, "too many decimals");
	ok(checkDecimals("1..1") == false, "adjacent decimals");
	ok(checkDecimals("1+2") == true, "no decimals");

	ok(checkOperators("1+1") == true, "correct addition");
	ok(checkOperators("1+1") == true, "correct subtraction");
	ok(checkOperators("1+1") == true, "correct addition");
	ok(checkOperators("1+1") == true, "correct addition");
	ok(checkOperators("1+1") == true, "correct addition");
	ok(checkOperators("1++1") == false, "Adjacent operators");
	ok(checkOperators("1+*1") == false, "Adjacent operators, mixed");
	ok(checkOperators("1*") == false, "Trailing operator");
        // infix2postfix
        ok (push(1)==0, "push successful test");
        ok (pop(1)!=NULL, "pop successful test");
        ok (pop(2)==NULL, "pop failed test");
        ok (priority('(')==0, "open bracket priority test successful");
        ok (priority('+')==1, "add priority test successful");
        ok (priority('-')==1, "subtract priority test successful");
        ok (priority('*')==2, "multiply priority test successful");
        ok (priority('/')==2, "division priority test successful");
        ok (priority('%')==3, "modulus priority test successful");
        ok (priority('^')==3, "power priority test successful");
        
            //vm
	ok (checker("ADD") == 0, "succesful");
	ok (checker("ADD") != 0, "Invalid instruction");
	ok (write2file(1.2) == 0, "succesful");
	ok (eval(1) == 0, "succesful");
	ok (eval(1) != 0, "unsuccesful");
	
        
}
