// interface functions for a concrete stack
// implemented as an array
// richard buckland 
// 28 April 2014 

#define MAX_STACK 100

typedef struct _stack {
  int contents[MAX_STACK];
  int size;
} stack;

int top (stack s);
stack pop (stack s);
stack push (stack s, int value);
int getSize(stack s);
