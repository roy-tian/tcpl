#include <stdio.h>
#include "roystring.h"

#define STRING_CAPACITY_HUGE 16383
#define STRING_CAPACITY 1023

int main() {
  ROY_STRING(str, STRING_CAPACITY_HUGE)
  ROY_STRING(buf, STRING_CAPACITY)
  FILE *fp = fopen("e123.java", "r+");
  while (fgets(buf, STRING_CAPACITY, fp)) {
    strcat(str, buf);
  }
  roy_string_replace_between(str, "/*", "*/\n", "");
  roy_string_replace_between(str, "//", "\n", "\n");

  printf("%s", str);
}