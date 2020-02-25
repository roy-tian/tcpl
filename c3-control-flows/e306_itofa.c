#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum { BUFFER_SIZE = 128 };

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

// Deprecated: use sprintf instead.
char * int64ToStrW(char * dest, int64_t number, size_t width) {
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
  size_t destWidth = pDest - dest;
  while (width-- > destWidth) {
    *pDest++ = ' ';
  }
  *pDest = '\0';
  return reverse(dest);
}

int main(void) {
  char buf[BUFFER_SIZE] = "\0";
  int64_t number = -13579246810LL;
  printf("%16lld\n", number);
  puts(int64ToStrW(buf, number, 16));
}