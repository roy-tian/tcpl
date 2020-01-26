#include "rpc.h"
#include "number.h"

void rpc(RoyShell * shell) {
  enum { STACK_CAPACITY = 128 };
  RoyStack * tokenStack = roy_stack_new(STACK_CAPACITY, (ROperate)roy_string_delete);
  RoyString * currentToken = roy_string_new(NULL);
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(currentToken, roy_shell_argument_at(shell, i));
    if (validNumber(currentToken)) {
      roy_stack_push(tokenStack, currentToken);
    } else if (validOperator(currentToken) && roy_stack_size(tokenStack) >= 2) { // enough tokenStack
      doOperate(tokenStack, currentToken);
    } else if (validOperator(currentToken) && roy_stack_size(tokenStack) < 2) {
      doError(tokenStack, currentToken, "tokens not enough.");
      return;
    } else {
      roy_string_prepend_str(currentToken, "unrecognised token - \'");
      roy_string_append_str(currentToken, "\'.");
      doError(tokenStack, currentToken, roy_string_cstr(currentToken));
      return; 
    }
  }
  if (roy_stack_size(tokenStack) > 1) {
    doError(tokenStack, currentToken, "parsing ends but stack not empty.");
    return;
  }
  printf("%.16g\n", *roy_stack_top(tokenStack, double));
  roy_string_delete(currentToken);
  roy_stack_delete(tokenStack);
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
  return roy_string_match(token, "[\\+\\-\\*/%%]");
}

void
doOperate(RoyStack        * tokenStack,
          const RoyString * token) {
  RoyString * operand1 = roy_stack_top(tokenStack, RoyString);
  roy_stack_pop(tokenStack);
  RoyString * operand2 = roy_stack_top(tokenStack, RoyString);
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