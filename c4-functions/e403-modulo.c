#include "../../roylib/roy.h"

void open_file(RoyDeque * parsed_line);

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_add_command(shell, "open", ROY_OPERATE(open_file));
  roy_shell_start(shell);
}