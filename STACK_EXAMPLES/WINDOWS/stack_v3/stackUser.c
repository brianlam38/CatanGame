// stack user
// uses abstract Stack
// compile as - "gcc -Wall -Werror -O -o output stackUser.c Stack.c"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Stack.h"

int main (int argc, char *argv[]) {
    

    printf ("testing concrete stack defined in stackImproved.h\n");

    printf("testing newStack\n");
    Stack s = newStack();
    printf("passed\n");

    printf("testing getSize\n");
    assert (getSize (s) == 0);
    printf("passed\n");

    printf("testing getMaxSize\n");
    assert (getMaxSize(s) == MAX_STACK);
    printf("passed\n");

    printf ("testing push\n");
    push (s, 5);
    assert (getSize (s) ==1);
    assert (top (s) == 5);

    push (s, 4);
    assert (getSize (s) ==2);
    assert (top (s) == 4);
    printf("passed\n");

    // now pop off the top element and check that
    // the stack returned has just one element in it

    printf ("testing pop\n");
    pop (s);
    assert (getSize (s) == 1);
    assert(top (s) == 5);

    pop (s);
    assert (getSize (s) == 0);
    printf("passed\n");

    printf ("All tests passed - you are awesome!\n");

    freeStack(s);
    return EXIT_SUCCESS;
}