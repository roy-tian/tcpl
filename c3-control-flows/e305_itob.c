#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum {
  BINARY      = 0b10,
  OCTONARY    =  010,
  DECIMAL     =   10,
  HEXDECIMAL  = 0x10,
  BUFFER_SIZE = 0x80
};

char * reverse(char * str) {
  char * pHead = str;
  char * pTail = str + strlen(str) - 1;
  while (pTail > pHead) {
    char temp = *pHead;
    *pHead++ = *pTail;
    *pTail-- = temp;
  }
  return str;
}

/* Deprecated: if decimal, octonary, or hexdecimal numbers are needed, use sprintf instead.
   Only use this for other rare condition. */
char * int64ToStrB(char * dest, int64_t number, int base) {
  bool pn = true, int64Min = false;
  if (number == LLONG_MIN) {
    int64Min = true;
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
  if (int64Min) {
    (*dest)++;
  }
  *pdest = '\0';
  return reverse(dest);
}

int main(void) {
  char buf[BUFFER_SIZE] = "\0";
  int64_t number = 224466881010LL;
  printf("%llX\n", number);
  puts(int64ToStrB(buf, number, HEXDECIMAL));
  printf("%lld\n", number);
  puts(int64ToStrB(buf, number, DECIMAL));
  printf("%llO\n", number);
  puts(int64ToStrB(buf, number, OCTONARY));
  puts(int64ToStrB(buf, number, BINARY));
}