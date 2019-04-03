#include <stdio.h>
#define STRING_CAPACITY

// Deprecated: this version won't be more effective than the std one.
int tolower_(int ch) {
  return ch >= 'A' && ch <= 'Z' ?
         ch + 32 : // ('a' - 'A') == 32
         ch;
}

int main(void) {
  char str[STRING_CAPACITY] = "PACK MY BOX WITH FIVE DOZEN LIQUOR JUGS.";
  puts(str);
  char * pstr = str + 1;
  while ((*pstr = tolower_(*pstr)) != '\0') {
    pstr++;
  }
  puts(str);
}