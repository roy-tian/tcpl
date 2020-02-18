#include "rpc.h"

void rpc(RoyShell * shell) {
  RoyStack * tokens = roy_stack_new(R_BUF_SIZE, (ROperate)roy_string_delete);
  for (size_t i = 1; i != roy_shell_argc(shell); i++) {
    RoyString * current = roy_shell_argv_at(shell, i);
    if (validNumber(current)) {
      roy_stack_push(tokens, roy_string_copy(current));
    } else if (validBinaryOperator(current) && roy_stack_size(tokens) >= 2) {
      RoyString * rhs = roy_string_copy(roy_stack_top(tokens, RoyString));
      roy_stack_pop(tokens);
      RoyString * lhs = roy_string_copy(roy_stack_top(tokens, RoyString));
      roy_stack_pop(tokens);
      RoyString * result = roy_string_new("");
      binary(result, lhs, rhs, current);
      roy_stack_push(tokens, result);
      roy_string_delete(rhs);
      roy_string_delete(lhs);
    } else {
      printf("Parse error at token - \'%s\'.\n", roy_string_cstr(current, 0));
      return; 
    }
  }
  if (roy_stack_size(tokens) > 1) {
    printf("Parsing ends with %d token(s) remains.\n",
            roy_stack_size(tokens));
  }
  roy_string_println(roy_stack_top(tokens, RoyString));
  roy_shell_log(shell, roy_stack_top(tokens, RoyString));
  roy_stack_delete(tokens);
}

void quit(RoyShell * shell) {
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}