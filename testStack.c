t = push (s, 'A');
assert (top (t) == 'A');


#define STACK_SIZE 1000

typedef struct _stack {
	char stack[STACK_SIZE];
	int size;
	int items;
} stack;

stack add (stack s, char elt);
stack top (stack s);
stack pop (stack s);



/* TESTSTACK.C */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "testStack.h"

#define SIZE 5

int main (int argc, char *argv[]) {

	char in[SIZE] = "max";
	char out[SIZE];

	stack buffer = newStack ();
	// load the string into the stack
	int pos;
	pos = 0;
	while (int pos != '\0') {
		push (buffer, in[pos]);
		pos++;
		assert (pos < SIZE);
	}

	// pop the string off the stack
	pos = 0;
	// buffer.numItems is concrete
	// getNumItems (buffer) is abstract (used since we can't know struct details)
	while (getNumItems (buffer) > 0) {			
		out[pos] = top (buffer);
		pos++;
		buffer = pop (buffer)
	}
	out[pos] = '\0';

	printf ("%s reversed is %s\n", in, out);











	stack s;
	stack t;

printf ("The size of the struct s is %d", sizeof (s));

	t = push (s, 'A'); // Pushing 'A' onto the stack
	assert (top (t) == 'A'); // Testing that the top of stack t has the element 'A'

	assert (s.items[0] == 'A') // Testing that the first element of stack t is 'A' (one elt has been pushed so far)

	// The 1st test only uses elements
	// The 2nd test takes a look inside the stack

	printf ("All tests passed. You are awesome!");
	return EXIT_SUCCESS;
}