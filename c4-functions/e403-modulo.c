#include "../../roylib/roy.h"

char content[STRING_CAPACITY_HUGE] = "\0";

void open(RoyShell * shell) {
  const char * name = roy_shell_argument_at(shell, 1);
  FILE * fp = fopen(name, "r");
  if (fp) {
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    memset(content, '\0', STRING_CAPACITY_HUGE);
    fread(content, sizeof(char), size, fp);
    printf("%s open successfully.\n", name);
  } else {
    puts("file not found.");
  }
  fclose(fp);
}

void show(RoyShell * shell) {
  if (content) {
    puts(content);
  } else {
    puts("nothing to show.");
  }
}

void quit(RoyShell * shell) {
  exit(EXIT_SUCCESS);
}

void error(RoyShell * shell) {
  printf("Unrecognised command: %s\n", roy_shell_argument_at(shell, 1));
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_add_command(shell, "open", open);
  roy_shell_add_command(shell, "show", show);
  roy_shell_add_command(shell, "quit", quit);
  roy_shell_add_command(shell, "", error);
  roy_shell_start(shell);
}