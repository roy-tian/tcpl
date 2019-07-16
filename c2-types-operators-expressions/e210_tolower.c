#include <stdio.h>
#define STRING_CAPACITY 1024

// Deprecated: this version won't be more effective than the std one.
int tolower_(int ch) {
  return ch >= 'A' && ch <= 'Z' ?
         ch + 32 : // ('a' - 'A') == 32
         ch;
}

void stringToLower(char * str) {
  char * pstr = str;
  while ((*pstr = tolower_(*pstr)) != '\0') {
    pstr++;
  } 
}

int main(void) {
  char str[STRING_CAPACITY] = "PACK MY BOX WITH FIVE DOZEN LIQUOR JUGS.";
  puts(str);
  stringToLower(str + 1);
  puts(str);
}