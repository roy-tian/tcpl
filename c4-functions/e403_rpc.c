/* you will need roylib to compile this file, like this:
 * gcc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "roy.h"

void rpc(RoyShell *);
void quit(RoyShell *);

bool validNumber(const RoyString *);
bool validOperator(const RoyString *);
void doNumber(RoyStack *, const RoyString *);
void doOperate(RoyStack *, const RoyString *);
void doError(RoyStack *, RoyString *, const char *);
double operate(double, double, int);

void rpc(RoyShell * shell) {
  enum { CAPACITY = 128 };
  RoyStack * tokens = roy_stack_new(CAPACITY, sizeof(double));
  RoyString * token = roy_string_new();
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(token, roy_shell_argument_at(shell, i));
    if (validNumber(token)) {
      doNumber(tokens, token);
    } else if (validOperator(token) && roy_stack_size(tokens) >= 2) { // enough tokenStack
      doOperate(tokens, token);
    } else if (validOperator(token) && roy_stack_size(tokens) < 2) {
      doError(tokens, token, "tokens not enough.");
      return;
    } else {
      roy_string_prepend_str(token, "unrecognised token - \'");
      roy_string_append_str(token, "\'.");
      doError(tokens, token, roy_string_cstr(token));
      return; 
    }
  }
  if (roy_stack_size(tokens) > 1) {
    doError(tokens, token, "parsing ends but stack not empty.");
    return;
  }
  printf("%.16g\n", *roy_stack_top(tokens, double));
  roy_string_delete(token);
  roy_stack_delete(tokens);
}

void quit(RoyShell * shell) {
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

bool
validNumber(const RoyString * token) {
  return roy_string_match(token, "[\\+\\-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][\\+\\-]?\\d+)?");
}

bool
validOperator(const RoyString * token) {
  return roy_string_match(token, "[\\+\\-\\*/%]");
}

void
doNumber(RoyStack        * tokenStack,
         const RoyString * token) {
  double value = atof(roy_string_cstr(token));
  roy_stack_push(tokenStack, &value);
}

void
doOperate(RoyStack        * tokenStack,
          const RoyString * token) {
  double operand1 = *roy_stack_top(tokenStack, double);
  roy_stack_pop(tokenStack);
  double operand2 = *roy_stack_top(tokenStack, double);
  roy_stack_pop(tokenStack);
  double result = operate(operand2, operand1, roy_string_at(token, 0));
  roy_stack_push(tokenStack, &result);
}

void
doError(RoyStack   * tokenStack,
        RoyString  * token,
        const char * errInfo) {
  printf("Syntax error: %s\n", errInfo);
  roy_string_delete(token);
  roy_stack_delete(tokenStack);
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