// stack user
// uses concrete stack
//compile using - "gcc -Wall -Werror -std=c99 -O -o output stack.c stackUser.c"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main (int argc, char *argv[]) {
    

    printf ("testing concrete stack defined in stackImproved.h\n");

    printf("testing newStack\n");
    stack s = newStack();
    printf("passed\n");

    printf("testing getSize\n");
    assert (getSize (s) == 0);
    printf("passed\n");

    printf("testing getMaxSize\n");
    assert (getMaxSize(s) == MAX_STACK);
    printf("passed\n");

    printf ("testing push\n");
    s = push (s, 'a');
    assert (getSize (s) ==1);
    assert (top (s) == 'a');

    s = push (s, 'b');
    assert (getSize (s) ==2);
    assert (top (s) == 'b');
    printf("passed\n");

    // now pop off the top element and check that
    // the stack returned has just one element in it

    printf ("testing pop\n");
    s = pop (s);
    assert (getSize (s) == 1);
    assert(top (s) == 'a');
    printf("passed\n");

    printf ("All tests passed - you are awesome!\n");

    return EXIT_SUCCESS;
}