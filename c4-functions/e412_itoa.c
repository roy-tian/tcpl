#include <stdio.h>

char str[128];
char *pstr = str;
void doItoa(int number, int radix);

void doItoa(int number, int radix) {
  if (number < 0) {
    *pstr++ = '-';
    number = -number;
  }
  if (number / radix != 0) {
    doItoa(number / radix, radix);
  }
  *pstr++ = '0' + number % 10;
}


int main(void) {
  int number = 31415926;
  doItoa(number, 10);
  puts(str);
}