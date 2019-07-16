#include <stdio.h>

// Deprecated: this version won't be more effective than the std one.
int tolower_(int ch) {
  return ch >= 'A' && ch <= 'Z' ?
         ch + 32 : // ('a' - 'A') == 32
         ch;
}

char * stringToLower(char * str) {
  char * pstr = str;
  while ((*pstr = tolower_(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

int main(void) {
  char str[] = "PACK MY BOX WITH FIVE DOZEN LIQUOR JUGS.";
  puts(str);
  stringToLower(str + 1);
  puts(str);
}