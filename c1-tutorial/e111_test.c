#include <stdio.h>
#include "roystring.h"

#define STRING_CAPACITY 1024

int main(void) {
  printf("      EMPTY STRING: %d\n", roy_string_count_word(""));
  printf("        ALL ENTERS: %d\n", roy_string_count_word("\n\n\n"));
  printf("         ALL CTRLS: %d\n", roy_string_count_word("\n \t"));
  printf("    BLANKS AT TAIL: %d\n", roy_string_count_word("Hello   "));
  printf("    BLANKS AT HEAD: %d\n", roy_string_count_word("   world"));
  printf("ONE WORD AT A LINE: %d\n",
         roy_string_count_word("It's\nfinger\nlicking\ngood.\n"));

}
