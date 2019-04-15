#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

enum NumberSystem {
  BINARY = 2,
  OCTONARY = 8,
  DECIMAL = 10,
  HEXDECIMAL = 16
};

char * roy_string_reverse(char * str);
// Deprecated:
// if decimal, octonary, or hexdecimal numbers are needed, use sprintf instead.
// Only use this for other rare condition.
char * roy_llong_to_string_base(char * dest, long long number, int base);

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

char * roy_llong_to_string_base(char * dest, long long number, int base) {
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
    int cur_digit = number % base;
    *pdest++ = cur_digit + (cur_digit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0);
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
  long long number = 224466881010;
  printf("%llX\n", number);
  puts(roy_llong_to_string_base(buf, number, HEXDECIMAL));
  printf("%lld\n", number);
  puts(roy_llong_to_string_base(buf, number, DECIMAL));
  printf("%llO\n", number);
  puts(roy_llong_to_string_base(buf, number, OCTONARY));
  puts(roy_llong_to_string_base(buf, number, BINARY));
}