#include "getword.h"

RoyString * content;

int main(int argc, char ** argv) {
  content = roy_string_read_file(argv[1]);
  if (!content) {
    exit(EXIT_FAILURE);
  }
  RoyMap * keytab = populateKeytab();
  RoyDeque * wordtab = populateWordtab();

  roy_deque_for_each(wordtab, (ROperate)add, keytab);
  bool printZero = true;
  roy_map_for_each(keytab, (ROperate)pairPrint, &printZero);

  roy_deque_delete(wordtab, NULL);
  roy_map_delete(keytab, NULL);
  roy_string_delete(content, NULL);
}