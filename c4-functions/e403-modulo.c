#include "../../roylib/roy.h"

char content[STRING_CAPACITY_HUGE] = "\0";

void open(RoyDeque * deque) {
  const char * name = roy_deque_at(deque, char, 1);
  FILE * fp = fopen(name, "r");
  if (fp) {
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fread(content, sizeof(char), size, fp);
    printf("%s open successfully.\n", name);
  } else {
    puts("file not found.");
  }
}

void show(RoyDeque * deque) {
  if (content) {
    puts(content);
  } else {
    puts("nothing to show.");
  }
}

void quit(RoyDeque * deque) {
  exit(EXIT_SUCCESS);
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_add_command(shell, "open", open);
  roy_shell_add_command(shell, "show", show);
  roy_shell_add_command(shell, "quit", quit);
  roy_shell_start(shell);
}