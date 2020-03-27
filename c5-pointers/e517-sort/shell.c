#include "sort.h"

void read(RoyShell * shell) {
  if (roy_shell_argc(shell) != 2) {
    puts("Bad command.");
    return;
  }
  RoyString * content =
    roy_string_read_file(roy_string_cstr(roy_shell_argv_at(shell, 1), 0));
  if (content) {
    roy_string_split(dir, content, "\n");
    printf("%zu lines read.\n", roy_deque_size(dir));
    roy_string_delete(content, NULL);
  }
}

void select(RoyShell * shell) {
  roy_deque_for_each(dir, (ROperate)roy_string_println, NULL);
}

void quit(RoyShell * shell) {
  roy_deque_delete(dir, NULL);
  roy_shell_delete(shell, NULL);
  exit(EXIT_SUCCESS);
}

void sort(RoyShell * shell) {
  Sort srt = STRING;
  if ( roy_shell_argv_find(shell, "-\\w*n\\w*|--number") > 0 ) {
    srt |= NUMBER;
  }
  if ( roy_shell_argv_find(shell, "-\\w*r\\w*|--reverse") > 0 ) {
    srt |= REVERSE;
  }
  if ( roy_shell_argv_find(shell, "-\\w*i\\w*|--insense") > 0 ) {
    srt |= INSENSE;
  }
  if ( srt == NUMBER + INSENSE || srt == NUMBER + REVERSE + INSENSE ) {
    printf("%d", srt);
    puts("Arguments error: 'n' and 'i' should never combine.");
    return;
  }
  roy_deque_sort(dir, comp(srt));
}
