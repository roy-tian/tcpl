#include "roynumber.h"
#include "roystring.h"
#include <ctype.h>

RoyUInteger roy_parse_hexadecimal(const char * str) {
  RoyUInteger ret = 0;
  if (strstr(str, "0X") == str || strstr(str, "0x") == str) {
    str += 2;
  }
  size_t len = strspn(str, "0123456789ABCDEFabcdef");
  for (size_t i = 0; i < len; i++) {
    ret *= 16;
    int cur_chr = *(str + i);
    if (isdigit(cur_chr)) {
      ret += cur_chr - '0';
    } else if (strchr("ABCDEF", *(str + i))) {
      ret += cur_chr - 'A' + 10;
    } else if (strchr("abcdef", *(str + i))) {
      ret += cur_chr - 'a' + 10;
    }
  }
  return ret;
}

