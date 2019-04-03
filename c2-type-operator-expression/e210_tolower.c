#include <stdio.h>

// Deprecated: this version won't be more effective than the std one.
int tolower_(int ch) {
  return ch >= 'A' && ch <= 'Z' ?
         ch + 32 : // ('a' - 'A') == 32
         ch;
}

int main(void) {
  
}