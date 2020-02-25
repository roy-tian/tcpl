#include <stdio.h>
#include <stdint.h>
#include <string.h>

enum {
  BUFFER_SIZE = 0x100,
  DWORD       = 0x20
};
size_t
uint64CountBit(uint64_t number) {
  size_t count = 0;
  // 'n & n - 1' deletes the rightmost '1' of n.
  for (; number != 0; number &= number - 1) { 
    count++;
  }
  return count;
}

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
  uint64_t num = 555666888ULL;

  printBin(num);
  printf("Number of 1: %zu\n", uint64CountBit(num));
}