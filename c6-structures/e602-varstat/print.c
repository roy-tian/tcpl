#include "varstat.h"

static void printVarTableRecord(const RoyString * string) {
  roy_string_print(string);
  putchar(' ');
}

void printVarTable(const RoyPair * pair) {
  roy_string_print(pair->key);
  printf(" [%zu]:\n", roy_set_size(pair->value));
  roy_set_for_each(pair->value, (ROperate)printVarTableRecord, NULL);
  putchar('\n');
}
