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

// 'dest' must be a string no shorter than 'length+1' characters.
char * roy_ullong_to_string_binary(char               * dest,
                            unsigned long long   number,
                            size_t               length);
unsigned long long
roy_ullong_right_rotate(unsigned long long   * number,
                        int                    times,
                        size_t                 length);
void print_clearly(char * binary);


char * roy_ullong_to_string_binary(char               * dest,
                            unsigned long long   number,
                            size_t               length) {
  for (int i = length - 1; i >= 0; i--) {
    *(dest + i) = number % 2 ? '1' : '0';
    number >>= 1;
  }
  return dest;
}

unsigned long long
roy_ullong_right_rotate(unsigned long long * number,
                        int                  times,
                        size_t               length) {
  unsigned long long end;
  end = (*number & ~(~0U << times)) << (length - times);
  *number >>= times;
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
    roy_ullong_right_rotate(&num, 1, DWORD);  
  }
}