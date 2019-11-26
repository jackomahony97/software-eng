/**
* The infix2postfix test.
* @author Hoang Anh Mai (117101156)
* @date 26/11/2019
*/
#include <ctap.h>
#include "infix2postfix.c"


TESTS {
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
        
}
