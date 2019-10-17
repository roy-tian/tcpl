#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

int64_t parseHexadecimal(const char * str) {
  int64_t ret = 0;
  int64_t pn = 1;
  if (strchr(str, '-') == str) {
    str += 1;
    pn = -1;
  } else if (strchr(str, '+') == str) {
    str += 1;
  }
  if (strstr(str, "0X") == str || strstr(str, "0x") == str) {
    str += 2;
  }
  size_t length = strspn(str, "0123456789ABCDEFabcdef");
  for (size_t i = 0; i < length; i++) {
    ret <<= 4;
    int currentChar = *(str + i);
    if (isdigit(currentChar)) {
      ret += currentChar - '0';
    } else if (strchr("ABCDEF", *(str + i))) {
      ret += currentChar - 'A' + 10;
    } else if (strchr("abcdef", *(str + i))) {
      ret += currentChar - 'a' + 10;
    }
  }
  return ret * pn;
}

int main(void) {
  char * str1 = "0x1234123f";
  char * str2 = "fantasy";
  char * str3 = "-123afCdE  ";
  char * str4 = "0x   ";
  printf("%12s | %16llX | %10lld\n",
         str1, parseHexadecimal(str1), parseHexadecimal(str1));
  printf("%12s | %16llX | %10lld\n",
         str2, parseHexadecimal(str2), parseHexadecimal(str2));
  printf("%12s | %16llX | %10lld\n",
         str3, parseHexadecimal(str3), parseHexadecimal(str3));
  printf("%12s | %16llX | %10lld\n",
         str4, parseHexadecimal(str4), parseHexadecimal(str4));
}