/* you will need roylib to compile this file, like this:
 * cc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "./rpc.h"

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}