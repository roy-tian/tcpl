#include <stdio.h>
#include <string.h>

enum {
  STRING_CAPACITY = 127,
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
};

size_t ullongCountBit(unsigned long long number);
char * ullongToBinaryString(char * dest, unsigned long long number, size_t length);
void printClearly(char * binary);

size_t ullongCountBit(unsigned long long number) {
  size_t count = 0;
  // 'n & n - 1' deletes the rightmost '1' of n.
  for (; number != 0; number &= number - 1) { 
    count++;
  }
  return count;
}

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
  char buf[STRING_CAPACITY] = "\0";
  unsigned long long num = 555666888;
  printClearly(ullongToBinaryString(buf, num, DWORD));
  printf("Number of 1: %zu", ullongCountBit(num));
}