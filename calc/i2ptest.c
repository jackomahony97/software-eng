#include <ctap.h>
#include "infix2postfix.c"
#include "virtualmachine.c"
#include "math.h"



TESTS {
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
