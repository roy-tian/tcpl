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

// 'dest' must be a string no shorter than 'width+1' characters.
char * roy_ullong_to_string_binary(char               * dest,
                                   unsigned long long   number,
                                   size_t               width);
unsigned long long roy_ullong_rotate_right(unsigned long long   * number,
                                           int                    steps,
                                           size_t                 width);
void print_clearly(char * binary);


char * roy_ullong_to_string_binary(char               * dest,
                                   unsigned long long   number,
                                   size_t               width) {
  for (int i = width - 1; i >= 0; i--) {
    *(dest + i) = number % 2 ? '1' : '0';
    number >>= 1;
  }
  return dest;
}

unsigned long long roy_ullong_rotate_right(unsigned long long * number,
                                           int                  steps,
                                           size_t               width) {
  unsigned long long end;
  end = (*number & ~(~0ULL << steps)) << (width - steps);
  *number >>= steps;
  *number |= end;
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
  ROY_STRING(buf, STRING_CAPACITY)
  unsigned long long num = 7654321;
  for (int i = 0; i != 10; i++) {
    print_clearly(roy_ullong_to_string_binary(buf, num, DWORD));
    roy_ullong_rotate_right(&num, 1, DWORD);  
  }
}