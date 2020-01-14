#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

char * uint64ToBinStr(char * dest, uint64_t number, size_t width);
// Behavior is undefined if 'position' and 'count' is invalid.
uint64_t uint64Invert(uint64_t * number, int position, size_t count);
void printClearly(const char * binary);

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
uint64Invert(uint64_t * number,
             int        position,
             size_t     count) {
  return *number = *number ^ ~(~0ULL << count) << (position + 1 - count);
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
  enum {
    BUFFER_SIZE = 1024,
    DWORD       = 32
  };

  char str[BUFFER_SIZE + 1] = "\0";
  uint64_t num = UINT_MAX;

  printClearly(uint64ToBinStr(str, num, DWORD));
  uint64Invert(&num, 10, 7);  
  printClearly(uint64ToBinStr(str, num, DWORD));
}