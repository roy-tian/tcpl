#include "roy.h"
#include "shell.h"

RoyStack  * stackOperand;
RoyVector * vectorVariable;
RoyShell  * shell;

int main(void) {
  enum {
    OPERAND_CAPACITY  = 128,
    VECTOR_CAPACITY   = 128,
    VECTOR_MAX_LENGTH = 128
  };
  stackOperand = roy_stack_new(OPERAND_CAPACITY, sizeof(double));
  vectorVariable = roy_vector_new(VECTOR_CAPACITY, sizeof(char) * VECTOR_MAX_LENGTH);
  shell = roy_shell_new();
  roy_shell_command_add(shell, "", rpc);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);  
}