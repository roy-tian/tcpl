#include "../roystring.h"
#include <stdio.h>

int main(void) {
  char * str1 = "0x1234123f";
  char * str2 = "fuckshit";
  char * str3 = "123afsd  ";
  char * str4 = "0x   ";
  printf("%s %X %u\n", str1, roy_string_htoi(str1), roy_string_htoi(str1));
  printf("%s %X %u\n", str2, roy_string_htoi(str2), roy_string_htoi(str2));
  printf("%s %X %u\n", str3, roy_string_htoi(str3), roy_string_htoi(str3));
  printf("%s %X %u\n", str4, roy_string_htoi(str4), roy_string_htoi(str4));
}