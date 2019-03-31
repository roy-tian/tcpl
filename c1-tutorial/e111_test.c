#include <stdio.h>
#include "roystring.h"

int main(void) {
  printf("      EMPTY STRING: %zu\n", roy_string_count_word(""));
  printf("        ALL ENTERS: %zu\n", roy_string_count_word("\n\n\n"));
  printf("         ALL CTRLS: %zu\n", roy_string_count_word("\n \t"));
  printf("    BLANKS AT TAIL: %zu\n", roy_string_count_word("Hello   "));
  printf("    BLANKS AT HEAD: %zu\n", roy_string_count_word("   world"));
  printf("ONE WORD AT A LINE: %zu\n", roy_string_count_word("It's\n"
                                                            "finger\n"
                                                            "licking\n"
                                                            "good.\n"));
}
