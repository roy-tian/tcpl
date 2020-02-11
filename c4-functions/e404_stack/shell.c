#include "stack.h"

void push(RoyShell * shell) {
  for (size_t i = 1; i != roy_shell_argc(shell); i++) {
    Double * temp =
      doubleNew(roy_string_to_double((roy_shell_argv_at(shell, i))));
    roy_stack_push(stack, temp);
  }
  printf("%zu element(s) pushed.\n", roy_shell_argc(shell) - 1);
}

void peek(RoyShell * shell) {
  if (!roy_stack_empty(stack)) {
    doublePrintln(roy_stack_top(stack, Double));
  } else {
    puts("Peek failed: stack is empty.");
  }
}

void pop(RoyShell * shell) {
  int count = 1;
  if (roy_shell_argc(shell) == 2) {
    count = roy_string_to_int((roy_shell_argv_at(shell, 1)));
  }
  if (count == 0) {
    puts("Pop failed: argument ill-formed.");
    return;
  }
  if (count > roy_stack_size(stack)) {
    printf("Warning: count (%d) is larger than the size of stack(%zu).",
           count, roy_stack_size(stack));
    count = roy_stack_size(stack);
  }
  for (size_t i = 0; i != count; i++) {
    roy_stack_pop(stack);
  }
  printf("%d element(s) popped.\n", count);
}

void swap(RoyShell * shell) {
  if (roy_stack_size(stack) >= 2) {
    Double * top1 = doubleCopy(roy_stack_top(stack, Double));
    roy_stack_pop(stack);
    Double * top2 = doubleCopy(roy_stack_top(stack, Double));
    roy_stack_pop(stack);
    roy_stack_push(stack, top1);
    roy_stack_push(stack, top2);
    puts("Top two elements swapped.");
  } else {
    puts("Swap failed: not enough elements.");
  }
}

void clear(RoyShell * shell) {
  while (!roy_stack_empty(stack)) {
    roy_stack_pop(stack);
  }
  puts("All elements cleared.");
}

void quit(RoyShell * shell) {
  roy_stack_delete(stack);
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}
