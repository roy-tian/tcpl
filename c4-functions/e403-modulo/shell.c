#include "rpc.h"

static bool doBinary(RoyStack * tokens, RoyString * current);

static RoyStack * tokens = NULL;

void rpc(RoyShell * shell) {
  if (!tokens) {
    tokens = roy_stack_new(R_BUF_SIZE, (ROperate)roy_string_delete);
  } else {
    roy_stack_clear(tokens);
  }
  for (size_t i = 1; i != roy_shell_argc(shell); i++) {
    RoyString * current = roy_shell_argv_at(shell, i);
    if (validNumber(current)) {
      roy_stack_push(tokens, roy_string_copy(current));
    } else if (validBinary(current) && roy_stack_size(tokens) >= 2) {
      if(!doBinary(tokens, current)) {
        return;
      }
    } else {
      printf("Unrecgonized token: %s\n", roy_string_cstr(current, 0));
      return; 
    }
  }
  if (roy_stack_size(tokens) > 1) {
    printf("Parsing ends with %zu tokens remain.\n", roy_stack_size(tokens));
  }
  roy_string_println(roy_stack_top(tokens, RoyString));
  roy_shell_log(shell, roy_stack_top(tokens, RoyString));
}

void quit(RoyShell * shell) {
  roy_shell_delete(shell);
  roy_stack_delete(tokens);
  roy_map_delete(operators);
  exit(EXIT_SUCCESS);
}

/* PRIVATE FUNCTIONS */

static bool
doBinary(RoyStack  * tokens,
         RoyString * current) {
  RoyString * rhs = roy_string_copy(roy_stack_top(tokens, RoyString));
  roy_stack_pop(tokens);
  RoyString * lhs = roy_string_copy(roy_stack_top(tokens, RoyString));
  roy_stack_pop(tokens);
  RoyString * result = roy_string_new("");
  binary(result, lhs, rhs, current);
  bool success = validNumber(result);
  if (success) {
    roy_stack_push(tokens, result);
  } else {
    printf("Calculate error: %s %s %s = %s\n",
            roy_string_cstr(lhs, 0),
            roy_string_cstr(current, 0),
            roy_string_cstr(rhs, 0),
            roy_string_cstr(result, 0));
    roy_string_delete(result);
  }
  roy_string_delete(rhs);
  roy_string_delete(lhs);
  return success;
}