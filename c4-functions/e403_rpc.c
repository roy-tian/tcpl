/* you will need roylib to compile this file, like this:
 * gcc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "roy.h"

void rpc(RoyShell * shell);
void quit(RoyShell * shell);

typedef double(*BinaryOperator)(double, double);
BinaryOperator charToBinaryOperator(int ch);

double plus(double operand1, double operand2);
double minus(double operand1, double operand2);
double times(double operand1, double operand2);
double divide(double operand1, double operand2);
double modulo(double operand1, double operand2);

void rpc(RoyShell * shell) {
  enum { STACK_CAPACITY = 128 };
  RoyStack * stack = roy_stack_new(STACK_CAPACITY, sizeof(double));
  RoyString * arg = roy_string_new();
  BinaryOperator op;
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (roy_string_match(arg,
                         "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?")) {  // arg is a number
      double value = atof(roy_string_cstr(arg));
      roy_stack_push(stack, &value);
    } else
    if ((op = charToBinaryOperator(roy_string_at(arg, 0))) &&   // arg is a binary operator
        roy_stack_size(stack) >= 2) {  // enough operand
      double operand1 = *roy_stack_top(stack, double);
      roy_stack_pop(stack);
      double operand2 = *roy_stack_top(stack, double);
      roy_stack_pop(stack);
      double result = op(operand2, operand1);
      roy_stack_push(stack, &result);
    } else {
      printf("Unrecognised token: %s\n", roy_string_cstr(arg));
      roy_string_delete(arg);
      roy_stack_delete(stack);
      return;
    }
  }
  if (roy_stack_size(stack) == 1) {
    printf("%.16g\n", *roy_stack_top(stack, double));
  } else {
    printf("Syntax error: stack not empty.\n");
  }
  roy_string_delete(arg);
  roy_stack_delete(stack);
}

void quit(RoyShell * shell) {
  roy_shell_delete(shell);
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

BinaryOperator charToBinaryOperator(int ch) {
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