#include "syntax.h"

Type * newStack(void) {
  return calloc(BUFFER_SIZE, sizeof(Type));
}

void deleteStack(Type * stack) {
  free(stack);
}

Type push(Type * stack) {
  stack[stack[0] + 1] = BRACKET_1 + stack[0] % 3;
  stack[0]++;
  return stack[stack[0]];
}

Type pop(Type * stack) {
  if (stack[0] <= 0) {
    return ERROR;
  }
  return stack[stack[0]--];
}
