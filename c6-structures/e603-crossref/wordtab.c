#include "crossref.h"

static void intPrint(int * val) {
  printf("%d ", *val);
}

int pairCompare(const RoyPair * lhs, const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}

void pairDelete(RoyPair * pair) {
  roy_string_delete(pair->key, NULL);
  roy_deque_delete(pair->value, NULL);
  free(pair);
}

void pairPrint(const RoyPair * pair) {
  if (roy_deque_size(pair->value) > 10) {
    printf("%s [%zu]\n",
          roy_string_cstr(pair->key, 0), roy_deque_size(pair->value));
    roy_deque_for_each(pair->value, (ROperate)intPrint, NULL);
    putchar('\n');
  }
}