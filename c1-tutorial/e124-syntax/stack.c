#include "syntax.h"

int * newStack(void) {
  return calloc(R_BUF_SIZE, sizeof(int));
}

void deleteStack(int * stack) {
  free(stack);
}

int push(int * stack) {
  stack[stack[0] + 1] = BRACKET_1 + stack[0] % 3;
  return stack[++stack[0]];
}

int pop(int * stack) {
  return stack[stack[0]--];
}
