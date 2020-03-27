#include "sort.h"

RoyDeque * dir;

int main(void) {
  RoyShell * shell = roy_shell_new();
  dir = roy_deque_new((ROperate)roy_string_delete);
  roy_shell_add(shell, read);
  roy_shell_add(shell, select);
  roy_shell_add(shell, sort);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}