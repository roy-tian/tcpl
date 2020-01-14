#include <stdio.h>

/// @deprecated this version won't be more effective than the std one.
int tolower_(int ch) {
  return ch >= 'A' && ch <= 'Z' ?
         ch + 32 : // ('a' - 'A') == 32
         ch;
}

char * stringToLower(char * str) {
  char * pStr = str;
  while ((*pStr = tolower_(*pStr)) != '\0') {
    pStr++;
  }
  return str;
}

int main(void) {
  char str[] = "PACK MY BOX WITH FIVE DOZEN LIQUOR JUGS.";
  puts(str);
  stringToLower(str + 1);
  puts(str);
}