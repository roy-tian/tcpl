#include "syntax.h"

RoyString * content;
RoyDeque  * matches;
int * shadow;

int main(int argc, char ** argv) {
  content = roy_string_read_file(argv[1]);
  if (!content) {
    exit(EXIT_FAILURE);
  }
  matches = roy_deque_new((ROperate)roy_match_delete);
  shadow = calloc(roy_string_length(content), sizeof(int));

  roy_string_tokenize( matches, content, 8,
    RE_COMMENT, RE_PREPROCESSOR, RE_TEXT, RE_KEYWORD, RE_TYPE, RE_VARIABLE, RE_NUMBER, RE_BRACKET );

  map();

  char out[R_BUF_SIZE] = "\0";
  strcpy(out, argv[1]);
  strcat(out, ".html");
  colorize(out);

  free(shadow);
  roy_deque_delete(matches, NULL);
  roy_string_delete(content, NULL);
}