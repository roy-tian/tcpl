#include "shell.h"

bool validNumber(RoyString * arg);
bool validVariable(RoyString * arg);
UnaryOperator validUnaryOperator(RoyString * arg);
BinaryOperator validBinaryOperator(RoyString * arg);

void doNumber(RoyString * arg);
void doVariable(RoyString * arg);
void doUnaryOperator(const UnaryOperator op);
void doBinaryOperator(const BinaryOperator op);
void doError(void);

void rpc(RoyShell * shell) {
  roy_stack_clear(operands);
  UnaryOperator unyOp;
  BinaryOperator binOp;
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    RoyString * arg =
    roy_string_new_with_content(roy_shell_argument_at(shell, i));
    if (validNumber(arg)) {
      doNumber(arg);
    } else
    if (unyOp = validUnaryOperator(arg)) {
      doUnaryOperator(unyOp);
    } else
    if (binOp = validBinaryOperator(arg)) {
      doBinaryOperator(binOp);
    } else
    if (validVariable(arg)) {
      doVariable(arg);
    } else {
      doError();
      roy_string_delete(arg);
      return;
    }
    roy_string_delete(arg);
  }
  roy_shell_log_append(shell, "%.16g", *roy_stack_top(operands, double));
}

void quit(RoyShell * shell) {
  exit(EXIT_SUCCESS);
}

bool validNumber(RoyString * arg) {
  return roy_string_match(arg, "^[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?$");
}

bool validVariable(RoyString * arg) {
  return roy_string_match(arg, "^[A-Za-z_]\\w*$") &&
         !strToUnaryOperator(roy_string_cstr(arg)) &&
         !strToBinaryOperator(roy_string_cstr(arg));
}

UnaryOperator validUnaryOperator(RoyString * arg) {
  UnaryOperator unyOp = strToUnaryOperator(roy_string_cstr(arg)); // unyOp not null: arg is a unary operator
  if (unyOp && !roy_stack_empty(operands)) {                      // stack not empty: enough operand
    return unyOp;
  }
  return NULL;
}

BinaryOperator validBinaryOperator(RoyString * arg) {
  BinaryOperator binOp = strToBinaryOperator(roy_string_cstr(arg));  // binOp not null: arg is a binary operator
  if (binOp && roy_stack_size(operands) >= 2) {      // stack size >= 2 : enough operands
    return binOp;
  }
  return NULL;
}

void doNumber(RoyString * arg) {
  double value = atof(roy_string_str(arg));
  roy_stack_push(operands, &value);
}

void doVariable(RoyString * arg) {
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
