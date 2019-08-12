#include "shell.h"

RoyShell * shell;
RoyVector * elements;

int main(void) {
  shell = roy_shell_new();
  elements = roy_vector_new(VECTOR_START_CAPACITY,
                            sizeof(char) * (STRING_CAPACITY + 1));
  roy_shell_command_add(shell, "insert", insert);
  roy_shell_command_add(shell, "read", read);
  roy_shell_command_add(shell, "select", select);
  roy_shell_command_add(shell, "sort", sort);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);
}