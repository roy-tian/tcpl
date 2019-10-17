/* you will need roylib to compile this file, like this:
 * gcc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "roy.h"

void rpc(RoyShell * shell);
void quit(RoyShell * shell);

bool validNumber(const RoyString * string);
bool validOperator(const RoyString * string);
void doNumber(RoyStack * stack, RoyString * string);
void doOperate(RoyStack * stack, RoyString * string);
void doError(RoyStack * stack, RoyString * string, const char * errInfo);
double operate(double operand1, double operand2, int operator_);

void rpc(RoyShell * shell) {
  enum { CAPACITY = 128 };
  RoyStack * stack = roy_stack_new(CAPACITY, sizeof(double));
  RoyString * arg = roy_string_new();
  bool parseSucess = true;
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (validNumber(arg)) {
      doNumber(stack, arg);
    } else if (validOperator(arg) && roy_stack_size(stack) >= 2) { // enough operands
      doOperate(stack, arg);
    } else if (validOperator(arg) && roy_stack_size(stack) < 2) {
      doError(stack, arg, "not enough operands.");
      return;
    } else {
      roy_string_insert_str(arg, "unrecognised token - \'", 0);
      roy_string_append_str(arg, "\'.");
      doError(stack, arg, roy_string_cstr(arg));
      return; 
    }
  }
  if (roy_stack_size(stack) > 1) {
    doError(stack, arg, "stack not empty.");
    return; 
  }
  printf("%.16g\n", *roy_stack_top(stack, double));
  roy_string_delete(arg);
  roy_stack_delete(stack);
}

void quit(RoyShell * shell) {
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

bool
validNumber(const RoyString * string) {
  return
  roy_string_match(string, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool
validOperator(const RoyString * string) {
  return strlen(roy_string_cstr(string)) == 1 && 
         strchr("+-*/%", roy_string_at(string, 0));
}

void
doNumber(RoyStack  * stack,
         RoyString * string) {
  double value = atof(roy_string_cstr(string));
  roy_stack_push(stack, &value);
}

void
doOperate(RoyStack  * stack,
          RoyString * string) {
  double operand1 = *roy_stack_top(stack, double);
  roy_stack_pop(stack);
  double operand2 = *roy_stack_top(stack, double);
  roy_stack_pop(stack);
  double result = operate(operand2, operand1, roy_string_at(string, 0));
  roy_stack_push(stack, &result);
}

void
doError(RoyStack   * stack,
        RoyString  * string,
        const char * errInfo) {
  printf("Syntax error: %s\n", errInfo);
  roy_string_delete(string);
  roy_stack_delete(stack);
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