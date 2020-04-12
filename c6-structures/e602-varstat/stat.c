#include "varstat.h"

int pairComp(const RoyPair * lhs, const RoyPair * rhs) {
  return strncmp(roy_string_cstr(lhs->key, 0),
                 roy_string_cstr(rhs->key, 0),
                 nsame);
}

void pairDelete(RoyPair * pair) {
  roy_set_delete(pair->value, (ROperate)roy_string_delete, NULL);
  roy_string_delete(pair->key, NULL);
  free(pair);
}

void add(const RoyMatch * match, RoyMap * vars) {
  RoyString * temp = roy_string_new_empty();
  roy_string_sub_match(temp, content, match);
  RoySet * ins = roy_map_find(vars, temp);
  if (!ins) {
    ins = roy_set_new();
    roy_set_insert(&ins, roy_string_copy(temp), (RCompare)roy_string_compare);
    roy_string_left(temp, temp, nsame);
    roy_map_insert(vars, temp, ins);
  } else {
    roy_set_insert(&ins, temp, (RCompare)roy_string_compare);
  }
}

bool var(const RoyMatch * match) {
  return match->type == VARIABLE;
}
