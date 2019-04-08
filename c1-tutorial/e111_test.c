#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

size_t roy_string_count_word(const char * str);

size_t roy_string_count_word(const char * str) {
  const char * pstr = str;
  size_t count = 0;
  bool flag = false;
  do {
    if (!flag && isalnum(*pstr)) {
      flag = true;
    } else if (flag && !isalnum(*pstr)) {
      flag = false;
      count++;
    }
  } while (*pstr++ != '\0');
  return count;
}

int main(void) {
  printf("     EMPTY STRING: %zu\n", roy_string_count_word(""));
  printf("       ALL ENTERS: %zu\n", roy_string_count_word("\n\n\n"));
  printf("        ALL CTRLS: %zu\n", roy_string_count_word("\n \t"));
  printf("   BLANKS AT TAIL: %zu\n", roy_string_count_word("Hello   "));
  printf("   BLANKS AT HEAD: %zu\n", roy_string_count_word("   world"));
  printf("ONE WORD PER LINE: %zu\n", roy_string_count_word("It's\n"
                                                           "finger\n"
                                                           "licking\n"
                                                           "good.\n"));
}