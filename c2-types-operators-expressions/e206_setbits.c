#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>

enum {
  BUFFER_SIZE = 0x100,
  DWORD       = 0x20
};

char *
uint64ToBinStr(char     * dest,
               uint64_t   number,
               size_t     width) {
  if (number > ~(0ULL << (width - 1))) {
    strcpy(dest, "overflow");
  } else {
    *(dest + width) = '\0';
    for (int i = width - 1; i >= 0; i--) {
      *(dest + i) = number % 2 ? '1' : '0';
      number >>= 1;
    }
  }
  return dest;
}

uint64_t
uint64SetBits(uint64_t * dest,
              int        position,
              size_t     count,
              uint64_t   src) {
  return *dest = (*dest & ~(~(~0ULL << count) << (position + 1 - count))) |
                 ( src  &   ~(~0ULL << count) << (position + 1 - count));
}

void
printClearly(const char * binary) {
  const char * pBinary = binary;
  while (*pBinary != '\0') {
    putchar(*pBinary);
    if ((pBinary - binary + 1) % 4 == 0) {
      putchar(' ');
    }
    pBinary++;
  }
  putchar('\b');
  putchar('\n');
}

void
printBin(uint64_t number) {
  char buf[BUFFER_SIZE] = "\0";
  printClearly(uint64ToBinStr(buf, number, DWORD));
}

int main(void) {
  uint64_t num1 = UINT_MAX;
  uint64_t num2 = 6552144ULL;

  printBin(num1);
  printBin(num2);
  uint64SetBits(&num1, 9, 10, num2);  
  printBin(num1);
}