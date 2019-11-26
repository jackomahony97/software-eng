/**
* Test uses TAP (Test Anyhing Protocal) to test calc
*/
#include <ctap.h>
#include "virtualmachine.c"
#include "math.h"


TESTS {
    //vm
	ok (checker("ADD") == 0, "succesful");
	ok (checker("ADD") != 0, "Invalid instruction");
	ok (write2file(1.2) == 0, "succesful");
	ok (eval(1) == 0, "succesful");
	ok (eval(1) != 0, "unsuccesful");
}


