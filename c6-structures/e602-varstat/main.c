#include "varstat.h"

RoyString * content;
int nsame;

int main(int argc, char ** argv) {

  const char * fileName = NULL;

  if ( !parseArgs(argc, argv, &fileName, &nsame) ||
       !(content = roy_string_read_file(fileName)) ) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  RoyDeque * matches = roy_deque_new((ROperate)roy_match_delete);
  /* The RoyMap vars:
     key:   first 'nsame' chars of variables
     value: a set to save every single distict variable */
  RoyMap * vars = roy_map_new((RCompare)pairComp, (ROperate)pairDelete);

  roy_string_tokenize(matches, content, 5,
    RE_COMMENT, RE_PREPROCESSOR, RE_TEXT, RE_KEYWORD, RE_VARIABLE);
  
  roy_deque_for_which(matches, (RCondition)var, (ROperate)add, vars);

  roy_map_for_each(vars, (ROperate)printVarTable, NULL);

  roy_map_delete(vars, NULL);
  roy_deque_delete(matches, NULL);
  roy_string_delete(content, NULL);
}
