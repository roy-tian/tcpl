#include "stack.h"

RoyStack * stack;

int main(void) {
  stack = roy_stack_new(1024, (ROperate)free);
  RoyShell * shell = roy_shell_new();
  roy_shell_add(shell, push);
  roy_shell_add(shell, peek);
  roy_shell_add(shell, pop);
  roy_shell_add(shell, swap);
  roy_shell_add(shell, clear);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}

