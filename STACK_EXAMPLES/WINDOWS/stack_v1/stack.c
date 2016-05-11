#include "stack.h"


int top (stack s){
   return s.contents[s.size-1];
}

stack pop (stack s) {
   s.size--;
   return s;
}

stack push (stack s, int value) {
   s.contents[s.size] = value;
   s.size++;
   return s;
}

int getSize (stack s) {
   return s.size;
}
