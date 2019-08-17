#ifndef SHELL_H
#define SHELL_H

#include "roy.h"

extern RoyShell * shell;
extern RoyVector * elements;

enum {
  VECTOR_START_CAPACITY = 10,
  STRING_CAPACITY = 255,
  SORT_PAGE = 1,
  SORT_SECTION = 1 << 1,
  SORT_INDEX = 1 << 2,
  SORT_REVERSELY = 1 << 3,
};

void insert(RoyShell * shell);
void read(RoyShell * shell);
void select(RoyShell * shell);
void sort(RoyShell * shell);
void shuffle(RoyShell * shell);
void quit(RoyShell * shell);
void error(RoyShell * shell);

#endif // SHELL_H