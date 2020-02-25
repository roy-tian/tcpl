#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum { BUFFER_SIZE = 128 };

char *
reverse(char * str) {
  char * pHead = str;
  char * pTail = str + strlen(str) - 1;
  while (pTail > pHead) {
    char temp = *pHead;
    *pHead++ = *pTail;
    *pTail-- = temp;
  }
  return str;
}

/* The 'abs' strategy calculates |digit| several times, so it is less efficient than this one.
   still deprecated: sprintf is a better choice with comprehensive format support. */
char *
int64ToStr(char    * dest,
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
  return reverse(dest);
}

int main(void) {
  char buf[BUFFER_SIZE] = "\0";
  int64_t number = 1133557799LL;
  printf("%lld\n", number);
  puts(int64ToStr(buf, number));
  printf("%lld\n", LLONG_MIN);
  puts(int64ToStr(buf, LLONG_MIN));
}