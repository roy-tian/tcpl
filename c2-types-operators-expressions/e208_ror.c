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
char * roy_number_to_binary(char * dest, unsigned long long number, NumberLength length);
// Behavior is undefined if 'position' and 'length' is invalid.
unsigned long long roy_number_invert(unsigned long long * number,
                            int         position,
                            size_t      length);
void print_clearly(char * binary);

char * roy_number_to_binary(char * dest, unsigned long long number, NumberLength length) {
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

unsigned long long roy_number_right_rotate(unsigned long long   * number,
                                  int           times,
                                  NumberLength  length) {
                                    unsigned long long end;
  ROY_STRING(str, STRING_CAPACITY)
  while (times-- > 0) {
    end = (*number & 1) << (length);
    *number >>= 1;
    print_clearly(roy_number_to_binary(str, end, DWORD));
    *number |= end;
  }
  return *number;
}


int main(void) {
  ROY_STRING(str, STRING_CAPACITY)
  unsigned long long num = 7654321;
  print_clearly(roy_number_to_binary(str, num, DWORD));
  roy_number_right_rotate(&num, 1, DWORD);  
  print_clearly(roy_number_to_binary(str, num, DWORD));
}