#ifndef SHELL_H
#define SHELL_H

#include "roy.h"

extern RoyShell * shell;
extern RoyVector * elements;

enum {
  VECTOR_START_CAPACITY = 10,
  BUFFER_SIZE = 256,
  SORT_STRING = 0,
  SORT_NUMBER = 1,
  SORT_REVERSELY = 1 << 1,
  SORT_INSENSITIVELY = 1 << 2,
  SORT_DIRECTORY = 1 << 3
};

void insert(RoyShell * shell);
void read(RoyShell * shell);
void select(RoyShell * shell);
void sort(RoyShell * shell);
void quit(RoyShell * shell);
void error(RoyShell * shell);

#endif // SHELL_H