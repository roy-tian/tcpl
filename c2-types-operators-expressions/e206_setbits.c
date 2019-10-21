#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>

enum {
  STRING_CAPACITY = 127,
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
};

char * uint64ToBinaryString(char * dest, uint64_t number, size_t width);
// Behavior is undefined if 'position' and 'count' is invalid.
uint64_t uint64SetBits(uint64_t *dest, int position, size_t count, uint64_t src);
void printClearly(const char * binary);

char *
uint64ToBinaryString(char     * dest,
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

int main(void) {
  char str[STRING_CAPACITY + 1] = "\0";
  uint64_t num1 = UINT_MAX;
  uint64_t num2 = 6552144;
  printClearly(uint64ToBinaryString(str, num1, DWORD));
  printClearly(uint64ToBinaryString(str, num2, DWORD));
  uint64SetBits(&num1, 9, 10, num2);  
  printClearly(uint64ToBinaryString(str, num1, DWORD));
}