#include <stdio.h>
#include <string.h>

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

int roy_ullong_count_bit(unsigned long long number);
char * roy_ullong_to_string_binary(char               * dest,
                            unsigned long long   number,
                            size_t               length);
void print_clearly(char * binary);


int roy_ullong_count_bit(unsigned long long number) {
  int count = 0;
  // 'n & n - 1' deletes the rightmost '1' of n.
  for (; number != 0; number &= number - 1) { 
    count++;
  }
  return count;
}

char * roy_ullong_to_string_binary(char               * dest,
                            unsigned long long   number,
                            size_t               length) {
  for (int i = length - 1; i >= 0; i--) {
    *(dest + i) = number % 2 ? '1' : '0';
    number >>= 1;
  }
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

int main(void) {
  ROY_STRING(buf, STRING_CAPACITY)
  unsigned long long num = 555666888;
  print_clearly(roy_ullong_to_string_binary(buf, num, DWORD));
  printf("Number of 1: %d", roy_ullong_count_bit(num));
}