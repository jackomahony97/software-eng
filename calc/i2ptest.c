#include <ctap.h>
#include <ctype.h>
#include "infix2postfix.c"


TESTS {
        ok (push(1)==0, "push test");
        ok (pop(1)!=NULL, "pop test");
        ok (pop(2)==NULL, "pop failed");
        ok (priority('(')==0, "open bracket test successful");
        ok (priority('+')==1, "add test successful");
        ok (priority('-')==1, "subtract test successful");
        ok (priority('*')==2, "multiply test successful");
        ok (priority('/')==2, "division test successful");
        ok (priority('%')==3, "modulus test successful");
        ok (priority('^')==3, "power test successful");
        
}
