#include <stdio.h>
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
char * ullongToBinaryString(char * dest, unsigned long long number, size_t base, size_t width, bool fill_zero);
unsigned long long ullongRoR(unsigned long long * number, int steps, size_t width);
void printClearly(char * binary);

char *
stringReverse(char * str) {
  char * pstr_head = str;
  char * pstr_tail = str + strlen(str) - 1;
  while (pstr_tail > pstr_head) {
    char temp = *pstr_head;
    *pstr_head++ = *pstr_tail;
    *pstr_tail-- = temp;
  }
  return str;
}

char *
ullongToBinaryString(char               * dest,
                     unsigned long long   number,
                     size_t               base,
                     size_t               width,
                     bool                 fill_zero) {
  char * pdest = dest;
  do {
    int cur_digit = number % base;
    *pdest++ = cur_digit + (cur_digit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0); 
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = fill_zero ? '0' : ' ';
  }
  *pdest = '\0';
  return stringReverse(dest);
}

unsigned long long
ullongRoR(unsigned long long * number,
          int                  steps,
          size_t               width) {
  unsigned long long right = (*number & ~(~0ULL << steps)) << (width - steps);
  *number >>= steps;
  *number |= right;
  return *number;
}


void
printClearly(char * binary) {
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
  unsigned long long num = 7654321;
  for (int i = 0; i != 20; i++) {
    printClearly(ullongToBinaryString(buf, num, 2, DWORD, true));
    ullongRoR(&num, 1, DWORD);  
  }
}