#include "../roynumber.h"
#include <stdio.h>

int main(void) {
  char * str1 = "0x1234123f";
  char * str2 = "fantasy";
  char * str3 = "123afCdE  ";
  char * str4 = "0x   ";
  printf("%s %lX %lu\n", str1, roy_parse_hexadecimal(str1), roy_parse_hexadecimal(str1));
  printf("%s %lX %lu\n", str2, roy_parse_hexadecimal(str2), roy_parse_hexadecimal(str2));
  printf("%s %lX %lu\n", str3, roy_parse_hexadecimal(str3), roy_parse_hexadecimal(str3));
  printf("%s %lX %lu\n", str4, roy_parse_hexadecimal(str4), roy_parse_hexadecimal(str4));
}