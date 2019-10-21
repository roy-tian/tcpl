#include <stdio.h>
#include <stdint.h>
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
char * int64ToString(char * dest, int64_t number);

char *
stringReverse(char * str) {
  char * pHead = str;
  char * pTail = str + strlen(str) - 1;
  while (pTail > pHead) {
    char temp = *pHead;
    *pHead++ = *pTail;
    *pTail-- = temp;
  }
  return str;
}

char *
int64ToString(char    * dest,
              int64_t   number) {
  bool pn = true, int64Min = false;
  if (number == LLONG_MIN) {
    int64Min = true;
    number++;
  }
  if (number < 0) {
    pn = false;
    number = -number;
  }
  char * pDest = dest;
  do {
    *pDest++ = '0' + number % 10;
  } while ((number /= 10) > 0);
  if (!pn) {
    *pDest++ = '-';
  }
  if (int64Min) {
    (*dest)++;
  }
  *pDest = '\0';
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