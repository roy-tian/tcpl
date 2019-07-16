#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum {
  STRING_CAPACITY = 127
};

char * roy_string_reverse(char * str);
// Deprecated: use sprintf instead.
char * roy_llong_to_string_width(char * dest, long long number, size_t width);

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

char * roy_llong_to_string_width(char * dest, long long number, size_t width) {
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
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = ' ';
  }
  *pdest = '\0';
  return roy_string_reverse(dest);
}

int main(void) {
  char buf[STRING_CAPACITY] = "\0";
  long long number = -13579246810;
  printf("%16lld\n", number);
  puts(roy_llong_to_string_width(buf, number, 16));
}