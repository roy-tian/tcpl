#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum {
  STRING_CAPACITY = 127
};

char * stringReverse(char * str);

// The 'abs' strategy calculates |digit| several times,
// so it is less efficient than this one.
// Deprecated: sprintf is a better choice for its comprehensive format support.
char * llongToString(char * dest, long long number);

char *
stringReverse(char * str) {
  char * pstr_head = str;
  char * pstr_tail = str + strlen(str) - 1;
  while (pstr_tail > pstr_head) {
    char temp = *pstr_head;
    *pstr_head++ = *pstr_tail;
    *pstr_tail-- = temp;
  }
  return str;
}

char *
llongToString(char      * dest,
              long long   number) {
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
  return stringReverse(dest);
}

int main(void) {
  char buf[STRING_CAPACITY + 1] = "\0";
  long long number = 1133557799;
  printf("%lld\n", number);
  puts(llongToString(buf, number));
  printf("%lld\n", LLONG_MIN);
  puts(llongToString(buf, LLONG_MIN));
}