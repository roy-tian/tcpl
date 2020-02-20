/* you will need roylib to compile this file, like this:
 * cc *.c -L"PATH_TO_ROYLIB" -lroylib lpcre2-8
 */

#include "rpc.h"

int main(void) {
  populateOperators();
  RoyShell * shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}