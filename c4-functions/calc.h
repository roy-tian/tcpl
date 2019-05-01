#include <stdio.h>

#define STACK_CAPACITY 1024

/* DATA STRUCTURES */

typedef struct _stack {
  double values[STACK_CAPACITY];
  size_t height;
} stack;

void push(stack * stk, double value);
double pop(stack * stk);
bool empty(stack * stk);
bool full(stack * stk);