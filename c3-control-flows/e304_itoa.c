#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_reverse(char * str);

// The 'abs' strategy calculates |digit| several times,
// so it is less efficient than this one.
// Deprecated: sprintf is a better choice for its comprehensive format support.
char * roy_llong_to_string(char * dest, long long number);

char * roy_string_reverse(char * str) {
  char * pstr_head = str;
  char * pstr_tail = str + strlen(str) - 1;
  while (pstr_tail > pstr_head) {
    char temp = *pstr_head;
    *pstr_head++ = *pstr_tail;
    *pstr_tail-- = temp;
  }
  return str;
}

char * roy_llong_to_string(char * dest, long long number) {
  bool pn = true, llong_min = false;
  if (number == LLONG_MIN) {
    llong_min = true;
    number++;
  }
  if (number < 0) {
    pn = false;
    number = -number;
  }
  char * pdest = dest;
  do {
    *pdest++ = '0' + number % 10;
  } while ((number /= 10) > 0);
  if (!pn) {
    *pdest++ = '-';
  }
  if (llong_min) {
    (*dest)++;
  }
  *pdest = '\0';
  return roy_string_reverse(dest);
}

int main(void) {
  ROY_STRING(buf, STRING_CAPACITY)
  printf("%d\n", 1133557799);
  puts(roy_llong_to_string(buf, 1133557799));
  printf("%lld\n", LLONG_MIN);
  puts(roy_llong_to_string(buf, LLONG_MIN));
}