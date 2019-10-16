#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

size_t
countWord(const char * str) {
  const char * pStr = str;
  size_t count = 0;
  bool flag = false;
  do {
    if (!flag && isalnum(*pStr)) {
      flag = true;
    } else if (flag && !isalnum(*pStr)) {
      flag = false;
      count++;
    }
  } while (*pStr++ != '\0');
  return count;
}

int main(void) {
  printf("  EMPTY STRING: %zu\n", countWord(""));
  printf("    ALL ENTERS: %zu\n", countWord("\n\n\n"));
  printf("     ALL CTRLS: %zu\n", countWord("\n \t"));
  printf("BLANKS AT TAIL: %zu\n", countWord("Hello   "));
  printf("BLANKS AT HEAD: %zu\n", countWord("   world"));
  printf("  ONE PER LINE: %zu\n", countWord("It's\nfinger\nlicking\ngood.\n"));
}