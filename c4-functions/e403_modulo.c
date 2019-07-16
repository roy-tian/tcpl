#include "../../roylib/roy.h"

const char * restrict DIGIT = "0123456789.eE";
const char * restrict OPERTOR = "+-*/%";

RoyStack * stack;

typedef double(*BinaryOperator)(double, double);

BinaryOperator binaryOperate(int ch);
double plus(double operand1, double operand2);
double minus(double operand1, double operand2);
double times(double operand1, double operand2);
double divide(double operand1, double operand2);
double modulo(double operand1, double operand2);
void rpc(const RoyShell * shell);

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
      pline++;
    } else
    if (strchr(OPERTOR, *pline)) { // current char is a operator.
      double operand1, operand2, result;
      if (roy_stack_size(stack) < 2) {
        fputs(stderr, "Syntex error.");
        return;
      } else {
        operand1 = *roy_stack_top(stack, double);
        roy_stack_pop(stack);
        operand2 = *roy_stack_top(stack, double);
        result = binaryOperate(*pline)(operand1, operand2);
        roy_stack_push(stack, &result);
      }
      pline++;
    } else
    if (isblank(*pline)) { 
      pline++;
    } else { // not digit, not operator, nor blank, it's invalid.
      fputs(stderr, "Syntex error.");
      return;
    }
  }
}

double plus(double operand1, double operand2) {
  return operand1 + operand2;
}

double minus(double operand1, double operand2) {
  return operand1 - operand2;
}

double times(double operand1, double operand2) {
  return operand1 * operand2;
}
double divide(double operand1, double operand2) {
  return operand1 / operand2;
}

double modulo(double operand1, double operand2) {
  return (double)((int)operand1 % (int)operand2);
}

BinaryOperator binaryOperate(int ch) {
  switch (ch) {
  case '+': return plus;
  case '-': return minus;
  case '*': return times;
  case '/': return divide;
  case '%': return modulo;
  default : return NULL; 
  }
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  stack = roy_stack_new(100, sizeof(double));

  roy_shell_add_command(shell, "", rpc);
  roy_shell_start(shell);
}