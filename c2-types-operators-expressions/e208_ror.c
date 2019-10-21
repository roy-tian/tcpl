#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum {
  STRING_CAPACITY = 127,
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
};

char * stringReverse(char * str);
char * uint64ToBinaryString(char * dest, uint64_t number, size_t base, size_t width, bool fillZero);
uint64_t uint64RoR(uint64_t * number, int steps, size_t width);
void printClearly(const char * binary);

char *
stringReverse(char * str) {
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
uint64ToBinaryString(char     * dest,
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
  return stringReverse(dest);
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
  char buf[STRING_CAPACITY + 1] = "\0";
  uint64_t num = 7654321ULL;
  for (int i = 0; i != 20; i++) {
    printClearly(uint64ToBinaryString(buf, num, 2, DWORD, true));
    uint64RoR(&num, 1, DWORD);  
  }
}