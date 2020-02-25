#include <stdio.h>

enum { BUFFER_SIZE = 128 };

/* Deprecated: non-recuresive version is easier to read and understand,
   yet 'itoa' is Windows-specified, 
   'sprintf' will bring more functionality and portability. */
void itoa_(int number, char * str, int radix) {
  static int index;
  if (number < 0) {
    str[0] = '-';
    number = -number;
  }
  if (number / radix != 0) {
    itoa_(number / radix, str, radix);
  }
  str[index++] = '0' + number % 10;
  str[index] = '\0';
}

int main(void) {
  char str[BUFFER_SIZE] = "\0";
  int number = 31415926;
  itoa_(number, str, 10);
  puts(str);
}