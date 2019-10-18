#include "roy.h"
#include <math.h>

enum { STACK_CAPACITY = 128 };

typedef double (* BinaryOperator)(double, double);
typedef double (* UnaryOperator)(double);

UnaryOperator strToUnaryOperator(const char *);
BinaryOperator strToBinaryOperator(const char *);

double plus(double, double);
double minus(double, double);
double times(double, double);
double divide(double, double);
double modulo(double, double);

void rpc(RoyShell *);
void quit(RoyShell *);

bool validNumber(const RoyString * arg);
UnaryOperator validUnaryOperator(const RoyString * arg);
BinaryOperator validBinaryOperator(const RoyString * arg);

void doNumber(const RoyString * arg);
void doUnaryOperator(UnaryOperator op);
void doBinaryOperator(BinaryOperator op);
void doError(const RoyString * arg);

void rpc(RoyShell * shell) {
  RoyStack * operands = roy_stack_new(STACK_CAPACITY, sizeof(double));
  RoyString * arg = roy_string_new();
  UnaryOperator unyOp;
  BinaryOperator binOp;
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (validNumber(arg)) {
      doNumber(arg);
    } else if ((unyOp = validUnaryOperator(arg))) {
      doUnaryOperator(unyOp);
    } else if ((binOp = validBinaryOperator(arg))) {
      doBinaryOperator(binOp);
    } else {
      doError(arg);
      roy_string_delete(arg);
      return;
    }
  }
  roy_shell_log_append(shell, "%.16g", *roy_stack_top(operands, double));
  roy_string_delete(arg);
}

void quit(RoyShell * shell) {
  roy_stack_delete(operands);
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

UnaryOperator strToUnaryOperator(const char * _operator) {
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

BinaryOperator strToBinaryOperator(const char * _operator) {
  if (strcmp(_operator, "+"  ) == 0) { return plus; }
  if (strcmp(_operator, "-"  ) == 0) { return minus; }
  if (strcmp(_operator, "*"  ) == 0) { return times; }
  if (strcmp(_operator, "/"  ) == 0) { return divide; }
  if (strcmp(_operator, "%"  ) == 0) { return modulo; }
  if (strcmp(_operator, "pow") == 0) { return pow; }
  return NULL; 
}


bool validNumber(const RoyString * arg) {
  return roy_string_match(arg, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool validVariable(const RoyString * arg) {
  return roy_string_match(arg, "[A-Za-z_]\\w*");
}

UnaryOperator validUnaryOperator(const RoyString * arg) {
  UnaryOperator unyOp = strToUnaryOperator(roy_string_cstr(arg)); // unyOp not null: arg is a unary operator
  if (unyOp && !roy_stack_empty(operands)) {                      // stack not empty: enough operand
    return unyOp;
  }
  return NULL;
}

BinaryOperator validBinaryOperator(const RoyString * arg) {
  BinaryOperator binOp = strToBinaryOperator(roy_string_cstr(arg));  // binOp not null: arg is a binary operator
  if (binOp && roy_stack_size(operands) >= 2) {      // stack size >= 2 : enough operands
    return binOp;
  }
  return NULL;
}

void doNumber(const RoyString * arg) {
  double value = atof(roy_string_cstr(arg));
  roy_stack_push(operands, &value);
}

void doUnaryOperator(UnaryOperator op) {
  double operand = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double result = op(operand);
  roy_stack_push(operands, &result);
}

void doBinaryOperator(BinaryOperator op) {
  double operand1 = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double operand2 = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double result = op(operand2, operand1);
  roy_stack_push(operands, &result);
}

void doError(const RoyString * arg) {
  printf("Unrecognised token: %s\n", roy_string_cstr(arg));
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}