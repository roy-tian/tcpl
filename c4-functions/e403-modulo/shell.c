#include "stdbool.h"
#include "shell.h"

static RoyDeque * parse(const char * line, RoyDeque * parsed);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->lines = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->parsed_line = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->cmd_dict = NULL;
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_deque_delete(shell->lines);
  roy_deque_delete(shell->parsed_line);
  roy_map_clear(shell->cmd_dict);
  free(shell);
}

void print(const char * str) {
  puts(str);
}

void
roy_shell_start(RoyShell * shell) {
  ROY_STRING(line, STRING_CAPACITY)
  while (true) {
    printf("> ");
    fgets(line, STRING_CAPACITY, stdin);
    roy_deque_push_back(shell->lines, line);
    parse(line, shell->parsed_line);
    roy_deque_for_each(shell->parsed_line, ROY_OPERATE(print));
  }
}

RoyShell *
roy_shell_add_command(RoyShell * shell, const char * cmd, void(*operate)(void *)) {
  roy_map_insert(shell->parsed_line, cmd, operate);
}

static RoyDeque *
parse(const char * line,
      RoyDeque   * parsed) {
  roy_deque_clear(parsed);
  const char * phead = line;
  const char * ptail = line;
  while (*phead != '\n') {
    if (!isgraph(*phead)) {
      phead++;
    } else {
      ptail = phead;
      do {
        ptail++;
      } while (isgraph(*ptail));
      ROY_STRING(arg, STRING_CAPACITY)
      strncpy(arg, phead, ptail - phead);
      roy_deque_push_back(parsed, arg);
      phead = ptail;
    }
  }
  return parsed;
}