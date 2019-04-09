#include <stdio.h>
#include <string.h>
#include <limits.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

typedef enum NumberLength_ {
  BYTE = 8,
  WORD = 16,
  DWORD = 32,
  QWORD = 64
} NumberLength;

// 'dest' must be a string no shorter than 65 characters.
char * roy_number_to_binary(char * dest, long long number, NumberLength length);
// Behavior is undefined if 'position' and 'length' is invalid.
long long roy_number_invert(long long * number,
                            int         position,
                            size_t      length);
void print_clearly(char * binary);

char * roy_number_to_binary(char * dest, long long number, NumberLength length) {
  int pn = 1;
  if (number < 0) {
    pn = 0;
    number = ~number;
    number += 1;
  }
  for (int i = length - 1; i != 0; i--) {
    *(dest + i) = number % 2 ? '1' : '0';
    number >>= 1;
  }
  *dest = pn ? '0' : '1';
  return dest;
}

long long roy_number_get_bits(long long number, int position, size_t length) {
  return (number >> (position + 1 - length)) & ~(~0 << length);
}

long long roy_number_invert(long long * number, int position, size_t length) {
  long long dest = *number;
  long long temp = *number;
  temp = ~roy_number_get_bits(temp, position, length);
  temp <<= (position + 1 - length);
  *number = (dest & (~0U << (position + 1))) +
            temp +
            (dest & ~(~0U << (position + 1 - length)));
  return *number;
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
  long long num = 7654321;
  print_clearly(roy_number_to_binary(str, num, DWORD));
  roy_number_invert(&num, 10, 7);  
  print_clearly(roy_number_to_binary(str, num, DWORD));
}