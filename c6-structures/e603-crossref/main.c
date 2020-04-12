#include "crossref.h"

int main(int argc, char ** argv) {
  RoyString * content = roy_string_read_file(argv[1]);
  if (!content) {
    exit(EXIT_FAILURE);
  }
  RoyDeque * words = roy_deque_new((ROperate)roy_match_delete);
  roy_string_tokenize(words, content, 3, RE_NOISEWORD, RE_WORD, RE_NEWLINE);

  RoyMap * wordtab = roy_map_new((RCompare)pairCompare, (ROperate)pairDelete);
  Pack pack = { 1, wordtab, content };
  roy_deque_for_each(words, (ROperate)stat, &pack);
  roy_map_for_each(wordtab, (ROperate)pairPrint, NULL);

  roy_map_delete(wordtab, NULL);
  roy_deque_delete(words, NULL);
  roy_string_delete(content, NULL);
}