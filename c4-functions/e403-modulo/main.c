#include "shell.h"

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_start(shell);
}