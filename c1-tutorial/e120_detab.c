#include "roystring.h"

#define TAB_SIZE 8

int main(void) {
  char str[STRING_CAPACITY] = 
    "Fly,\tfly,\tfly\tyour\tkite,\n"
    "High  \t  in   \tthe\t sky;\t\n"
    "\t  \t \t\n"
    "\tUp and \t\t down,\n"
    "   \tRound and round,\n"
    "Let \tyour\t kite fly high.";
  const char * file_name = "e120.txt";

  roy_string_write_to_file("ORIGINAL STRING\n=============\n", file_name);
  roy_string_append_to_file(str, file_name);
  roy_string_append_to_file("\n\nDETABED STRING\n============\n", file_name);
  roy_string_append_to_file(roy_string_detab(str, TAB_SIZE), file_name);
}
