#include "shell.h"

RoyShell * shell;
RoyVector * elements;

int main(void) {
  shell = roy_shell_new();
  elements = roy_vector_new(VECTOR_START_CAPACITY,
                            sizeof(char) * (STRING_CAPACITY + 1));
  roy_shell_add(shell, insert);
  roy_shell_add(shell, read);
  roy_shell_add(shell, select);
  roy_shell_add(shell, sort);
  roy_shell_add(shell, quit);
  roy_shell_default(shell, error);
  roy_shell_start(shell);
}