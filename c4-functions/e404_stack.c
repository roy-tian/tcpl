#include "roy.h"

RoyStack * stack;

void push(RoyShell * shell) {
  for (size_t i = 1; i != roy_shell_argc(shell); i++) {
    roy_stack_push(stack, roy_string_copy(roy_shell_argv_at(shell, i)));
  }
  printf("%zu element(s) pushed.\n", roy_shell_argc(shell) - 1);
}

void peek(RoyShell * shell) {
  if (!roy_stack_empty(stack)) {
    roy_string_println(roy_stack_top(stack, RoyString));
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
    printf("Warning: count (%d) is oversized (%zu), this will only clear the stack.\n",
           count, roy_stack_size(stack));
    count = roy_stack_size(stack);
  }
  for (int i = 0; i != count; i++) {
    roy_stack_pop(stack);
  }
  printf("%d element(s) popped.\n", count);
}

void swap(RoyShell * shell) {
  if (roy_stack_size(stack) >= 2) {
    RoyString * top1 = roy_string_copy(roy_stack_top(stack, RoyString));
    roy_stack_pop(stack);
    RoyString * top2 = roy_string_copy(roy_stack_top(stack, RoyString));
    roy_stack_pop(stack);
    roy_stack_push(stack, top1);
    roy_stack_push(stack, top2);
    puts("Top two elements swapped.");
  } else {
    puts("Swap failed: not enough elements.");
  }
}

void clear(RoyShell * shell) {
  roy_stack_clear(stack);
  puts("All elements cleared.");
}

void quit(RoyShell * shell) {
  roy_stack_delete(stack);
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

int main(void) {
  stack = roy_stack_new(R_BUF_SIZE, (ROperate)roy_string_delete);
  RoyShell * shell = roy_shell_new();
  roy_shell_add(shell, push);
  roy_shell_add(shell, peek);
  roy_shell_add(shell, pop);
  roy_shell_add(shell, swap);
  roy_shell_add(shell, clear);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}
