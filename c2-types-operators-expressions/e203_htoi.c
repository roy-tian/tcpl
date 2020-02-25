#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

int64_t parseHex(const char * str) {
  int64_t ret = 0;
  int64_t pn = 1;
  if (strncmp(str, "-", 1) == 0) {
    str += 1;
    pn = -1;
  } else if (strncmp(str, "+", 1) == 0) {
    str += 1;
  }
  if (strncmp(str, "0X", 2) == 0 || strncmp(str, "0x", 2) == 0) {
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

void
test(const char * str) {
  int64_t hex = parseHex(str);
  printf("%12s | %10llX | %10lld\n", str, hex, hex);
}

int main(void) {
  test("0x1234123f");
  test("fantasy");
  test("123afCdE  ");
  test("0x   ");
}