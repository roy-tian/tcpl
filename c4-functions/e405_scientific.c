#include "../../roylib/roy.h"
#include <math.h>

const char * restrict DIGIT = "0123456789.eE";
const char * restrict OPERTOR = "+-*/%";

void rpc(RoyShell *);
void quit(RoyShell *);

typedef double (* BinaryOperator)(double, double);
typedef double (* UnaryOperator)(double);
const UnaryOperator charToUnaryOperator(const char *);
const BinaryOperator charToBinaryOperator(const char *);
double plus(double, double);
double minus(double, double);
double times(double, double);
double divide(double, double);
double modulo(double, double);

void rpc(RoyShell * shell) {
  enum { STACK_CAPACITY = 128 };
  RoyStack * stack = roy_stack_new(STACK_CAPACITY, sizeof(double));
  UnaryOperator unyOp;
  BinaryOperator binOp;
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    const char * arg = roy_shell_argument_at(shell, i);
    if (strspn(arg, DIGIT) == strlen(arg)) {  // arg is a number
      double value = atof(arg);
      roy_stack_push(stack, &value);
    } else
    if ((binOp = charToBinaryOperator(arg)) &&  // arg is a binary operator
        roy_stack_size(stack) >= 2) {     // enough operands
      double operand1 = *roy_stack_top(stack, double);
      roy_stack_pop(stack);
      double operand2 = *roy_stack_top(stack, double);
      roy_stack_pop(stack);
      double result = binOp(operand2, operand1);
      roy_stack_push(stack, &result);
    } else 
    if ((unyOp = charToUnaryOperator(arg)) &&   // arg is a unary operator
        !roy_stack_empty(stack)) {        // has operand
      double operand = *roy_stack_top(stack, double);
      double result = unyOp(operand);
      roy_stack_push(stack, &result);
    } else {
      puts("Syntax error.");
      roy_stack_delete(stack);
      return;
    }
  }
  roy_shell_log_append(shell, "%.16g", *roy_stack_top(stack, double));
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

const UnaryOperator charToUnaryOperator(const char * _operator) {
  if (strcmp(_operator, "sin"  ) == 0) { return sin; }
  if (strcmp(_operator, "cos"  ) == 0) { return cos; }
  if (strcmp(_operator, "tan"  ) == 0) { return tan; }
  if (strcmp(_operator, "sqrt" ) == 0) { return sqrt; }
  if (strcmp(_operator, "exp"  ) == 0) { return exp; }
  if (strcmp(_operator, "log"  ) == 0) { return log; }
  if (strcmp(_operator, "log10") == 0) { return log10; }
  if (strcmp(_operator, "log2" ) == 0) { return log2; }
  return NULL;
}

const BinaryOperator charToBinaryOperator(const char * _operator) {
  if (strcmp(_operator, "+"  ) == 0) { return plus; }
  if (strcmp(_operator, "-"  ) == 0) { return minus; }
  if (strcmp(_operator, "*"  ) == 0) { return times; }
  if (strcmp(_operator, "/"  ) == 0) { return divide; }
  if (strcmp(_operator, "%"  ) == 0) { return modulo; }
  if (strcmp(_operator, "pow") == 0) { return pow; }
  return NULL; 
}


int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_command_add(shell, "", rpc);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);
}