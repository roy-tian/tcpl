#include "../../roylib/roy.h"

const char * DIGIT = "0123456789.eE";

RoyStack * stack;

int isfloat(int ch) {
  return isdigit(ch) || (strchr(".eE", ch) ? 1 : 0);
}

int isoperator(int ch) {
  return strchr("+-*/^%", ch) ? 1 : 0;
}

// Reverse Polish Calculator
void rpc(const RoyShell * shell) {
  const char * pline = roy_shell_line(shell);
  char buf[STRING_CAPACITY + 1] = "\0";
  int index = 0;
  while (*pline != '\0') {
    if (strchr(DIGIT, *pline)) { // current char is a first shown digit of pline.
      size_t dec_len = strspn(pline, DIGIT);
      strncpy(buf, pline, dec_len);
      roy_stack_push(stack, &buf);
    } else if (isoperator(*pline)) {
      if (index != 0) {
        buf[index] = '\0';
        double temp = atof(buf);
        roy_stack_push(stack, &temp);
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