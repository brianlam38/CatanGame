//stack user

// uses concrete stack

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main (int argc, char *argv[]) {


    printf ("testing concrete stack defined in stackImproved.h\n");
    stack s;
    s.size = 0;

    assert (s.size == 0);

    s = push (s, 5);
    assert (s.size ==1);
    assert (top (s) == 5);

    s = push (s, 4);
    assert (s.size ==2);
    assert (top (s) == 4);

    // now pop off the top element and check that
    // the stack returned has just one element in it
    s = pop (s);
    assert (s.size == 1);

    printf ("All tests passed - you are awesome!\n");

    return EXIT_SUCCESS;
}
