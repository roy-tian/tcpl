#include "shell.h"

bool validNumber(const RoyString * arg);
bool validVariable(const RoyString * arg);
UnaryOperator validUnaryOperator(const RoyString * arg);
BinaryOperator validBinaryOperator(const RoyString * arg);

void doNumber(const RoyString * arg);
void doVariable(const RoyString * arg);
void doUnaryOperator(const UnaryOperator op);
void doBinaryOperator(const BinaryOperator op);
void doError(void);

void rpc(RoyShell * shell) {
  roy_stack_clear(operands);
  UnaryOperator unyOp;
  BinaryOperator binOp;
  RoyString * arg = roy_string_new();
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (validNumber(arg)) {
      doNumber(arg);
    } else
    if ((unyOp = validUnaryOperator(arg))) {
      doUnaryOperator(unyOp);
    } else
    if ((binOp = validBinaryOperator(arg))) {
      doBinaryOperator(binOp);
    } else
    if (validVariable(arg)) {
      doVariable(arg);
    } else {
      doError();
      roy_string_delete(arg);
      return;
    }
  }
  roy_shell_log_append(shell, "%.16g", *roy_stack_top(operands, double));
  roy_string_delete(arg);
}

void quit(RoyShell * shell) {
  roy_stack_delete(operands);
  roy_map_delete(variables);
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
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

void doVariable(const RoyString * arg) {
  double value;
  if (roy_map_find(variables, roy_string_cstr(arg))) {
    value = *roy_map_at(variables, double, roy_string_cstr(arg));
  } else {
    value = atof(roy_shell_ohistory_at(shell, -1));
    roy_map_insert(variables, roy_string_cstr(arg), &value);
  }
  roy_stack_push(operands, &value);
}

void doUnaryOperator(const UnaryOperator op) {
  double operand = *roy_stack_top(operands, double);
  double result = op(operand);
  roy_stack_push(operands, &result);
}

void doBinaryOperator(const BinaryOperator op) {
  double operand1 = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double operand2 = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double result = op(operand2, operand1);
  roy_stack_push(operands, &result);
}

void doError(void) {
  puts("Syntax error.");
}
