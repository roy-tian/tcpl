#include "../../../roylib/roy.h"

struct _RoyShell {
  RoyDeque * lines;
  RoyDeque * parsed_line;
  RoyMap   * cmd_dict;
};

typedef struct _RoyShell RoyShell;

RoyShell * roy_shell_new(void);

void roy_shell_delete(RoyShell * shell);

void roy_shell_start(RoyShell * shell);

RoyShell * roy_shell_add_command(RoyShell * shell, const char * cmd, void(*operate)(void *));