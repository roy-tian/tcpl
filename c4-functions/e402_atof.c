#include <stdio.h>
#include <string.h>
#include <stdbool.h>

double roy_parse_double(const char * str) {
  str += strspn(str, " \t");
  double result = 0.0;
  bool pn = true;
  if (*str == '-') {
    str++;
    pn = false;
  }
}

int main(void) {
  printf("%g", atof("123.45e-6"));
}