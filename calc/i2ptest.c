#include <ctap.h>
#include "infix2postfix.c"

char mul="*";
char plus="+";
char sub="-";
char div="/";
char mod="%";
char pow="^";
char one="1";
char open_bracket="(";
char close_bracket=")";

TEST {
        ok (push(one)==0, "successful");
        ok (push(one)==1, "failed");
        ok (pop(one)!=NULL, "successful");
        ok (pop(one)==NULL, "failed");
        ok (priority(open_bracket)==0, "successful");
        ok (priority(close_bracket)==0, "successful");
        ok (priority(plus)==1, "successful");
        ok (priority(sub)==1, "successful");
        ok (priority(mul)==2, "successful");
        ok (priority(div)==2, "successful");
        ok (priority(mod)==3, "successful");
        ok (priority(pow)==3, "successful");
        
}
