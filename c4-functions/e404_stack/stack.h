#ifndef E404_STACK
#define E404_STACK

#include "roy.h"

extern RoyStack * stack;

typedef struct {
  double value;
} Double;

Double * doubleNew(double value);
Double * doubleCopy(const Double * dbl);
void     doublePrintln(const Double * dbl);

void     push (RoyShell * shell);
void     pop  (RoyShell * shell);
void     peek (RoyShell * shell);
void     swap (RoyShell * shell);
void     clear(RoyShell * shell);
void     quit (RoyShell * shell);

#endif // E404_STACK
