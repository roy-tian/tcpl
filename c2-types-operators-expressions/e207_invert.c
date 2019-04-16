#include <stdio.h>
#include <string.h>
#include <limits.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

enum NumberLength {
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
};

char * roy_ullong_to_string_binary(char               * dest,
                                   unsigned long long   number,
                                   size_t               width);
// Behavior is undefined if 'position' and 'count' is invalid.
unsigned long long roy_ullong_invert(unsigned long long * number,
                                     int                  position,
                                     size_t               count);
void print_clearly(char * binary);

char * roy_ullong_to_string_binary(char               * dest,
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

unsigned long long roy_ullong_invert(unsigned long long * number,
                                     int                  position,
                                     size_t               count) {
  return *number = *number ^ ~(~0ULL << count) << (position + 1 - count);
}

void print_clearly(char * binary) {
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
  ROY_STRING(str, STRING_CAPACITY)
  unsigned long long num = UINT_MAX;
  print_clearly(roy_ullong_to_string_binary(str, num, DWORD));
  roy_ullong_invert(&num, 10, 7);  
  print_clearly(roy_ullong_to_string_binary(str, num, DWORD));
}