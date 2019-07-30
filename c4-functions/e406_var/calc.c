#include <math.h>
#include <stdio.h>
#include "calc.h"

const char * DIGIT = "0123456789.eE";
const char * OPERTOR = "+-*/%";

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

BinaryOperator charToBinaryOperator(const char * _operator) {
  if (strcmp(_operator, "+"  ) == 0) { return plus; }
  if (strcmp(_operator, "-"  ) == 0) { return minus; }
  if (strcmp(_operator, "*"  ) == 0) { return times; }
  if (strcmp(_operator, "/"  ) == 0) { return divide; }
  if (strcmp(_operator, "%"  ) == 0) { return modulo; }
  if (strcmp(_operator, "pow") == 0) { return pow; }
  return NULL; 
}

UnaryOperator charToUnaryOperator(const char * _operator) {
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