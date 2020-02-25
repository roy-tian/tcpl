#include "shell.h"
#include <time.h>

RoyShell * shell;
RoyVector * elements;

int main(void) {
  srand(time(NULL));
  shell = roy_shell_new();
  elements = roy_vector_new(VECTOR_START_CAPACITY,
                            sizeof(char) * (BUFFER_SIZE));
  roy_shell_add(shell, insert);
  roy_shell_add(shell, read);
  roy_shell_add(shell, select);
  roy_shell_add(shell, sort);
  roy_shell_add(shell, shuffle);
  roy_shell_add(shell, quit);
  roy_shell_default(shell, error);
  roy_shell_start(shell);
}