#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

int isdigit_(int ch, int base) {
  if (base >= 1 && base <= 10) {
    return (ch >= '0' && ch <= '0' + base);
  } else if (base >= 11 && base <= 36) {
    return ( isdigit(ch) ||
             (ch >= 'a' && ch <= 'a' + base - 11) ||
             (ch >= 'A' && ch <= 'A' + base - 11) );
  } else
    return 0;
}

int vdigit(int ch) {
  if (isdigit(ch)) {
    return ch - '0';
  }
  if (ch >= 'a' && ch <= 'z') {
    return ch - 'a' + 10;
  }
  if (ch >= 'A' && ch <= 'Z') {
    return ch - 'A' + 10;
  }
  return -1;
}

// std version 'strtoll' / 'test' are more effective.
int strtoi_(const char * restrict str, char ** restrict endstr, int base) {
  if (base < 0 || base > 36) {
    return 0;
  }
  while (isspace(*str)) {
    str++;
  }
  int pn = 1;
  if (*str == '+') {
    str++;
  }
  if (*str == '-') {
    pn = -1;
    str++;
  } 
  if ( base == 16 && (strstr(str, "0x") == str || strstr(str, "0X") == str) ) {
    str += 2;
  }
  if (base == 0) {
    if ( strstr(str, "0x") == str || strstr(str, "0X") == str) {
      str += 2;
      base = 16;
    } else if (strchr(str, '0') == str) {
      base = 8;
    } else {
      base = 10;
    }
  }
  int ret = 0;
  while (isdigit_(*str, base)) {
    ret *= base;
    ret += vdigit(*str);
    str++;
  }
  if (endstr) {
    *endstr = (char *)str;
  }
  return ret * pn;
}

void test(const void * str, int base) {
  char * endstr;
  int val = strtoimax(str, &endstr, base);
  printf("%s -> %d | %s\n", str, val, endstr);
      val = strtoi_(str, &endstr, base);
  printf("%s -> %d | %s\n", str, val, endstr);
}

int main(void) {
  test("   -123junk", 10);
  test("10101010", 2);
  test("XyZ", 36);
  test(" Hahahaha  ~!@#", 36);
  test("0100", 0);
  test("100", 0);
  test("0x100",0);
}