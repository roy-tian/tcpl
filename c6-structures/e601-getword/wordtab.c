#include "getword.h"

RoyDeque * populateWordtab(void) {
  RoyDeque * ret = roy_deque_new((ROperate)roy_match_delete);

  roy_string_tokenize( ret, content,
    4, RE_COMMENT, RE_PREPROCESSOR, RE_TEXT, "[A-Za-z_][0-9A-Za-z_]*" );
  return ret;
}

void add(const RoyMatch * match, RoyMap * keytab) {
  RoyString * temp = roy_string_new_empty();
  roy_string_sub_match(temp, content, match);
  int * found;
  if ( (found = roy_map_find(keytab, temp)) != NULL ) {
    (*found)++;
  }
}