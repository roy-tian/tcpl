/* you will need roylib to compile this file, like this:
 * gcc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "../../roylib/roy.h"

const char * restrict DIGIT = "0123456789.eE";
const char * restrict OPERTOR = "+-*/%";

typedef double(*BinaryOperator)(double, double);

void rpc(RoyShell * shell);
// Handles the number at the beginning of 'line', pushes it into 'stack', returns the length of the number.
size_t doNumber(const char * line, RoyStack * stack);
// Handles the operator at the beginning of 'line', uses the first two doubles on the top of 'stack' as operands, calculates the result, pushes it back into 'stack', returns 1 if success.
size_t doOperator(const char * line, RoyStack * stack);
void doError(void);
void quit(RoyShell * shell);

BinaryOperator binaryOperate(int ch);
double plus(double operand1, double operand2);
double minus(double operand1, double operand2);
double times(double operand1, double operand2);
double divide(double operand1, double operand2);
double modulo(double operand1, double operand2);

// Reverse Polish Calculator
void rpc(RoyShell * shell) {
  RoyStack * stack = roy_stack_new(100, sizeof(double));
  const char * pline = roy_shell_line(shell);
  while (*pline != '\0') {
    if (strchr(DIGIT, *pline)) { // current char is a first shown digit of pline.
      pline += doNumber(pline, stack);
    } else
    if (strchr(OPERTOR, *pline)) { // current char is a operator.
      if (doOperator(pline, stack) == 1) {
        pline++;
      } else {
        doError();
        return;
      }
    } else
    if (isblank(*pline)) { 
      pline++;
    } else { // not digit, not operator, nor blank, it's invalid.
       doError();
       return;
    }
  }
  if (roy_stack_size(stack) == 1) {
    printf("%.16g\n", *roy_stack_top(stack, double));
  } else {
    doError();
  }
}

size_t doNumber(const char * line, RoyStack * stack) {
  size_t numLen = strspn(line, DIGIT);
  char buf[STRING_CAPACITY + 1] = "\0";
  strncpy(buf, line, numLen);
  double result = atof(buf);
  roy_stack_push(stack, &result);
  return numLen;
}

size_t doOperator(const char * line, RoyStack * stack) {
  if (roy_stack_size(stack) < 2) {
    return 0;
  } else {
    double operand1 = *roy_stack_top(stack, double);
    roy_stack_pop(stack);
    double operand2 = *roy_stack_top(stack, double);
    roy_stack_pop(stack);
    double result = binaryOperate(*line)(operand2, operand1);
    roy_stack_push(stack, &result);
    return 1;
  }
}

void doError(void) {
  puts("Syntex error.");
}

void quit(RoyShell * shell) {
  exit(EXIT_SUCCESS);
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
  roy_shell_add_command(shell, "", rpc);
  roy_shell_add_command(shell, "quit", quit);
  roy_shell_start(shell);
}