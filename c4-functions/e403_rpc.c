/* you will need roylib to compile this file, like this:
 * gcc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "../../roylib/roy.h"

const char * restrict DIGIT = "0123456789.eE";
const char * restrict BINARY_OPERTOR = "+-*/%";

void rpc(RoyShell * shell);
void quit(RoyShell * shell);

typedef double(*BinaryOperator)(double, double);
const BinaryOperator charToBinaryOperator(int ch);
double plus(double operand1, double operand2);
double minus(double operand1, double operand2);
double times(double operand1, double operand2);
double divide(double operand1, double operand2);
double modulo(double operand1, double operand2);

void rpc(RoyShell * shell) {
  enum { STACK_CAPACITY = 128 };
  RoyStack * stack = roy_stack_new(STACK_CAPACITY, sizeof(double));
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    const char * arg = roy_shell_argument_at(shell, i);
    if (strspn(arg, DIGIT) == strlen(arg)) {  // arg is a number
      double value = atof(arg);
      roy_stack_push(stack, &value);
    } else
    if (charToBinaryOperator(arg) &&               // arg is a binary operator
        roy_stack_size(stack) >= 2) {  // enough operand
      double operand1 = *roy_stack_top(stack, double);
      roy_stack_pop(stack);
      double operand2 = *roy_stack_top(stack, double);
      roy_stack_pop(stack);
      double result = charToBinaryOperator(*arg)(operand2, operand1);
      roy_stack_push(stack, &result);
    } else {
      roy_shell_output_append(shell, "Syntax error.");
      return;
    }
  }
  roy_shell_output_append(shell, "%.16g", *roy_stack_top(stack, double));
  roy_stack_delete(stack);
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

const BinaryOperator charToBinaryOperator(int ch) {
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
  roy_shell_command_add(shell, "", rpc);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);
}