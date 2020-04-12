#include "crossref.h"

void stat(const RoyMatch * match, Pack * pack) {
  if (match->type == WORD) {
    RoyString * temp = roy_string_new_empty();
    roy_string_sub_match(temp, pack->content, match);
    RoyDeque * ins = roy_map_find(pack->wordtab, temp);
    int * index = malloc(sizeof(int));
    *index = pack->index;
    if (!ins) {
      ins = roy_deque_new((ROperate)free);
      roy_deque_push_back(ins, index);
      roy_map_insert(pack->wordtab, temp, ins);
    } else {
      roy_deque_push_back(ins, index);
    }
  } else if (match->type == NEWLINE) {
    pack->index++;
  }
}