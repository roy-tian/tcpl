#include "roy.h"
#include "shell.h"

RoyStack * operands;
RoyMap   * variables;
RoyShell * shell;

int main(void) {
  enum {
    STACK_CAPACITY  = 128,
    BUFFER_SIZE = 128
  };
  operands  = roy_stack_new(STACK_CAPACITY, sizeof(double));
  variables = roy_map_new(sizeof(char) * (BUFFER_SIZE),
                          sizeof(double),
                          ROY_COMPARE(strcmp));
  shell     = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, playback);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);  
}