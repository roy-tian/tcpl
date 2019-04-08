#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long roy_parse_hexadecimal(const char * str);

long long roy_parse_hexadecimal(const char * str) {
  long long ret = 0;
  long long pn = 1;
  if (strchr(str, '-') == str) {
    str += 1;
    pn = -1;
  } else if (strchr(str, '+') == str) {
    str += 1;
  }
  if (strstr(str, "0X") == str || strstr(str, "0x") == str) {
    str += 2;
  }
  size_t len = strspn(str, "0123456789ABCDEFabcdef");
  for (size_t i = 0; i < len; i++) {
    ret <<= 4;
    int cur_chr = *(str + i);
    if (isdigit(cur_chr)) {
      ret += cur_chr - '0';
    } else if (strchr("ABCDEF", *(str + i))) {
      ret += cur_chr - 'A' + 10;
    } else if (strchr("abcdef", *(str + i))) {
      ret += cur_chr - 'a' + 10;
    }
  }
  return ret * pn;
}

int main(void) {
  char * str1 = "0x1234123f";
  char * str2 = "fantasy";
  char * str3 = "-123afCdE  ";
  char * str4 = "0x   ";
  printf("%12s | %16llX | %10lld\n", str1, roy_parse_hexadecimal(str1), roy_parse_hexadecimal(str1));
  printf("%12s | %16llX | %10lld\n", str2, roy_parse_hexadecimal(str2), roy_parse_hexadecimal(str2));
  printf("%12s | %16llX | %10lld\n", str3, roy_parse_hexadecimal(str3), roy_parse_hexadecimal(str3));
  printf("%12s | %16llX | %10lld\n", str4, roy_parse_hexadecimal(str4), roy_parse_hexadecimal(str4));
}