#include <stdio.h>

// Bad idea: non-recuresive version is easier to read and understand.
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
  int number = 31415926;
  char str[100] = "\0";
  itoa_(number, str, 10);
  puts(str);
}