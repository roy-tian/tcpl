#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

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

char * roy_string_reverse(char * str);
char * roy_ullong_to_string(char * dest, unsigned long long number, size_t base, size_t width, bool fill_zero);
unsigned long long roy_ullong_rotate_right(unsigned long long * number, int steps, size_t width);
void print_clearly(char * binary);

char *
roy_string_reverse(char * str) {
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
roy_ullong_to_string(char               * dest,
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
  return roy_string_reverse(dest);
}

unsigned long long
roy_ullong_rotate_right(unsigned long long * number,
                        int                  steps,
                        size_t               width) {
  unsigned long long right = (*number & ~(~0ULL << steps)) << (width - steps);
  *number >>= steps;
  *number |= right;
  return *number;
}


void
print_clearly(char * binary) {
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
  for (int i = 0; i != 20; i++) {
    print_clearly(roy_ullong_to_string(buf, num, 2, DWORD, true));
    roy_ullong_rotate_left(&num, 1, DWORD);  
  }
}