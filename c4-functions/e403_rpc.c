/* you will need roylib to compile this file, like this:
 * gcc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "roy.h"

void rpc(RoyShell * shell);
void quit(RoyShell * shell);

bool validNumber(const RoyString * arg);
bool validOperator(const RoyString * arg);
void doNumber(RoyStack * operands, RoyString * arg);
void doOperate(RoyStack * operands, RoyString * arg);
void doError(RoyStack * operands, RoyString * arg, const char * errInfo);
double operate(double operand1, double operand2, int operator_);

void rpc(RoyShell * shell) {
  enum { CAPACITY = 128 };
  RoyStack * operands = roy_stack_new(CAPACITY, sizeof(double));
  RoyString * arg = roy_string_new();
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (validNumber(arg)) {
      doNumber(operands, arg);
    } else if (validOperator(arg) && roy_stack_size(operands) >= 2) { // enough operands
      doOperate(operands, arg);
    } else if (validOperator(arg) && roy_stack_size(operands) < 2) {
      doError(operands, arg, "operands not enough.");
      return;
    } else {
      roy_string_prepend_str(arg, "unrecognised token - \'");
      roy_string_append_str(arg, "\'.");
      doError(operands, arg, roy_string_cstr(arg));
      return; 
    }
  }
  if (roy_stack_size(operands) > 1) {
    doError(operands, arg, "operands not empty.");
    return;
  }
  printf("%.16g\n", *roy_stack_top(operands, double));
  roy_string_delete(arg);
  roy_stack_delete(operands);
}

void quit(RoyShell * shell) {
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

bool
validNumber(const RoyString * arg) {
  return roy_string_match(arg, "[\\+\\-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][\\+\\-]?\\d+)?");
}

bool
validOperator(const RoyString * arg) {
  return roy_string_match(arg, "[\\+\\-\\*/%]");
}

void
doNumber(RoyStack  * operands,
         RoyString * arg) {
  double value = atof(roy_string_cstr(arg));
  roy_stack_push(operands, &value);
}

void
doOperate(RoyStack  * operands,
          RoyString * arg) {
  double operand1 = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double operand2 = *roy_stack_top(operands, double);
  roy_stack_pop(operands);
  double result = operate(operand2, operand1, roy_string_at(arg, 0));
  roy_stack_push(operands, &result);
}

void
doError(RoyStack   * operands,
        RoyString  * arg,
        const char * errInfo) {
  printf("Syntax error: %s\n", errInfo);
  roy_string_delete(arg);
  roy_stack_delete(operands);
}

double
operate(double operand1,
        double operand2,
        int    operator_) {
  switch (operator_) {
  case '+': return operand1 + operand2;
  case '-': return operand1 - operand2;
  case '*': return operand1 * operand2;
  case '/': return operand1 / operand2;
  case '%': return (double)((int)operand1 % (int)operand2);
  default : return 0.0;
  } 
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}