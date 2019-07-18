#include "../../roylib/roy.h"

RoyStack * stack;

void push(RoyShell * shell) {
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    double temp = atof(roy_shell_argument_at(shell, i));
    roy_stack_push(stack, &temp);
  }
  printf("%zu element(s) pushed.\n", roy_shell_argument_count(shell) - 1);
}

void peek(RoyShell * shell) {
  if (!roy_stack_empty(stack)) {
    printf("%.16g\n", *roy_stack_top(stack, double));
  } else {
    puts("Peek failed: stack is empty.");
  }
}

void pop(RoyShell * shell) {
  size_t count = 1;
  if (roy_shell_argument_count(shell) == 2) {
    count = atoi(roy_shell_argument_at(shell, 1));
  }
  if (count < 0) {
    count = 0;
  }
  if (count > roy_stack_size(stack)) {
    count = roy_stack_size(stack);
  }
  for (int i = 0; i != count; i++) {
    roy_stack_pop(stack);
  }
  printf("%d element(s) popped.\n", count);
}

void swap(RoyShell * shell) {
  if (roy_stack_size(stack) >= 2) {
    double top1 = *roy_stack_top(stack, double);
    roy_stack_pop(stack);
    double top2 = *roy_stack_top(stack, double);
    roy_stack_pop(stack);
    roy_stack_push(stack, &top1);
    roy_stack_push(stack, &top2);
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
  exit(EXIT_SUCCESS);
}

int main(void) {
  stack = roy_stack_new(1024, sizeof(double));
  RoyShell * shell = roy_shell_new();
  roy_shell_add_command(shell, "push", push);
  roy_shell_add_command(shell, "peek", peek);
  roy_shell_add_command(shell, "pop", pop);
  roy_shell_add_command(shell, "swap", swap);
  roy_shell_add_command(shell, "clear", clear);
  roy_shell_add_command(shell, "quit", quit);
  roy_shell_start(shell);
}

