#include <stdio.h>
#include <string.h>
#include <limits.h>

enum {
  STRING_CAPACITY = 1023,
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
};

char * ullongToBinaryString(char * dest, unsigned long long number, size_t width);
// Behavior is undefined if 'position' and 'count' is invalid.
unsigned long long ullongInvert(unsigned long long * number, int position, size_t count);
void printClearly(char * binary);

char * ullongToBinaryString(char               * dest,
                            unsigned long long   number,
                            size_t               width) {
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

unsigned long long ullongInvert(unsigned long long * number,
                                int                  position,
                                size_t               count) {
  return *number = *number ^ ~(~0ULL << count) << (position + 1 - count);
}

void printClearly(char * binary) {
  char * pbinary = binary;
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

int main(void) {
  char str[STRING_CAPACITY] = "\0";
  unsigned long long num = UINT_MAX;
  printClearly(ullongToBinaryString(str, num, DWORD));
  ullongInvert(&num, 10, 7);  
  printClearly(ullongToBinaryString(str, num, DWORD));
}