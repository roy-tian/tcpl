#include "../../roylib/roy.h"

RoyStack * stack;

int isfloat(int ch) {
  return isdigit(ch) || (strchr(".eE", ch) ? 1 : 0);
}

// Reverse Polish Calculator
void rpc(const RoyShell * shell) {
  const char * pcmd = roy_shell_line(shell);
  char buf[STRING_CAPACITY + 1] = "\0";
  int index = 0;
  while (*pcmd != '\0') {
    if (isfloat(*pcmd)) {
      buf[index++] = *pcmd;
    } else {
      if (strlen(buf) != 0) {
        double value = atof(buf);
        roy_stack_push(stack, &value);
        index = 0;
        *buf = '\0';
      }
    }
  }
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  stack = roy_stack_new(100, sizeof(double));

  roy_shell_add_command(shell, "", rpc);
  roy_shell_start(shell);
}