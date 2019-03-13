#include <stdio.h>
#include "roystring.h"

#define STRING_CAPACITY 1024

int main(void) {
  char str[STRING_CAPACITY] = "Red Orange Yellow Green Blue Indigo Violet";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("\n'Roy G. Biv' STANDS FOR:\n%s\n", roy_string_replace_all(str, " ", "\n"));
}