#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

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

char * roy_llong_to_string_binary(char * dest, long long number, size_t length);
// Behavior is undefined if 'position' and 'count' is invalid.
long long roy_llong_set_bits(long long * dest,
                             int         position,
                             size_t      count,
                             long long   src);
void print_clearly(char * binary);

char * roy_llong_to_string_binary(char * dest, long long number, size_t length) {
  int pn = 1;
  if (number > (1 << (length - 1)) - 1 || number < -(1 << (length - 1))) {
    strcpy(dest, "overflow");
  } else {
  if (number < 0) {
    pn = 0;
    number = ~number + 1;
  }
  for (int i = length - 1; i != 0; i--) {
    *(dest + i) = number % 2 ? '1' : '0';
    number >>= 1;
  }
  *dest = pn ? '0' : '1';
  }
  return dest;
}

long long roy_llong_set_bits(long long * dest,
                             int         position,
                             size_t      count,
                             long long   src) {
  return *dest = (*dest & ~(~(~0U << count) << (position + 1 - count))) |
                 ( src  &   ~(~0U << count) << (position + 1 - count));
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
  long long num1 = INT_MAX;
  long long num2 = 6552144;
  print_clearly(roy_llong_to_string_binary(str, num1, DWORD));
  print_clearly(roy_llong_to_string_binary(str, num2, DWORD));
  roy_llong_set_bits(&num1, 9, 10, num2);  
  print_clearly(roy_llong_to_string_binary(str, num1, DWORD));
}