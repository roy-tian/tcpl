#include "stack.h"

Double *
doubleNew(double value) {
  Double * ret = malloc(sizeof(Double));
  ret->value = value;
  return ret;
}

Double *
doubleCopy(const Double * dbl) {
  Double * ret = malloc(sizeof(double));
  ret->value = dbl->value;
  return ret;
}

void
doublePrintln(const Double * dbl) {
  printf("%.16g\n", dbl->value);
}