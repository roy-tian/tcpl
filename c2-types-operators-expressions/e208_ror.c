#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum {
  BUFFER_SIZE = 0x100,
  DWORD       = 0x20
};

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

char *
uint64ToBinStr(char     * dest,
               uint64_t   number,
               size_t     base,
               size_t     width,
               bool       fillZero) {
  char * pDest = dest;
  do {
    int currentDigit = number % base;
    *pDest++ = currentDigit + (currentDigit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0); 
  size_t destWidth = pDest - dest;
  while (width-- > destWidth) {
    *pDest++ = fillZero ? '0' : ' ';
  }
  *pDest = '\0';
  return reverse(dest);
}

uint64_t
uint64RoR(uint64_t * number,
          int        steps,
          size_t     width) {
  uint64_t right = (*number & ~(~0ULL << steps)) << (width - steps);
  *number >>= steps;
  *number |= right;
  return *number;
}

void
printClearly(const char * binary) {
  const char * pbinary = binary;
  while (*pbinary != '\0') {
    putchar(*pbinary);
    if ((pbinary - binary + 1) % 4 == 0) {
      putchar(' ');
    }
    pbinary++;
  }
  putchar('\b');
  putchar('\n');
}

void
printBin(uint64_t number) {
  char buf[BUFFER_SIZE] = "\0";
  printClearly(uint64ToBinStr(buf, number, 2, DWORD, true));
}

int main(void) {
  uint64_t num = 7654321ULL;

  for (int i = 0; i != 20; i++) {
    printBin(num);
    uint64RoR(&num, 1, DWORD);  
  }
}