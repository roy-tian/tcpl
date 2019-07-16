#include <stdio.h>
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

char * ullongToBinaryString(char * dest, unsigned long long number, size_t width);
// Behavior is undefined if 'position' and 'count' is invalid.
unsigned long long ullongSetBits(unsigned long long *dest, int position, size_t count, unsigned long long src);
void printClearly(const char * binary);

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

unsigned long long ullongSetBits(unsigned long long * dest,
                                 int                  position,
                                 size_t               count,
                                 unsigned long long   src) {
  return *dest = (*dest & ~(~(~0ULL << count) << (position + 1 - count))) |
                 ( src  &   ~(~0ULL << count) << (position + 1 - count));
}

void printClearly(const char * binary) {
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

int main(void) {
  char str[STRING_CAPACITY + 1] = "\0";
  unsigned long long num1 = UINT_MAX;
  unsigned long long num2 = 6552144;
  printClearly(ullongToBinaryString(str, num1, DWORD));
  printClearly(ullongToBinaryString(str, num2, DWORD));
  ullongSetBits(&num1, 9, 10, num2);  
  printClearly(ullongToBinaryString(str, num1, DWORD));
}