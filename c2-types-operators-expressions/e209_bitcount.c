#include <stdio.h>
#include <stdint.h>
#include <string.h>

enum {
  STRING_CAPACITY = 127,
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
};

size_t uint64CountBit(uint64_t number);
char * uint64ToBinStr(char * dest, uint64_t number, size_t length);
void printClearly(char * binary);

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
printClearly(char * binary) {
  char * pBinary = binary;
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
  char buf[STRING_CAPACITY + 1] = "\0";
  uint64_t num = 555666888;
  printClearly(uint64ToBinStr(buf, num, DWORD));
  printf("Number of 1: %zu", uint64CountBit(num));
}