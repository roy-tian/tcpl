#include "roy.h"

extern RoyDeque * dir;

typedef enum Sort {
  STRING  = 0,
  NUMBER  = 1,
  REVERSE = 1 << 1,
  INSENSE = 1 << 2
} Sort;

void read(RoyShell * shell);
void select(RoyShell * shell);
void sort(RoyShell * shell);
void quit(RoyShell * shell);
void list(RoyShell * shell);

RCompare comp(Sort sort_);
