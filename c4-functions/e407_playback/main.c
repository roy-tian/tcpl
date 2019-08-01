#include "roy.h"
#include "shell.h"

RoyStack * operands;
RoyMap   * variables;
RoyShell * shell;

int main(void) {
  enum {
    STACK_CAPACITY  = 128,
    STRING_CAPACITY = 127
  };
  operands  = roy_stack_new(STACK_CAPACITY, sizeof(double));
  variables = roy_map_new(sizeof(char) * (STRING_CAPACITY + 1),
                          sizeof(double),
                          ROY_COMPARE(strcmp));
  shell     = roy_shell_new();
  roy_shell_command_add(shell, "", rpc);
  roy_shell_command_add(shell, "playback", playback);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);  
}