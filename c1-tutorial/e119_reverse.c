#include "roystring.h"
#include <stdio.h>

int main(void) {
  char str[STRING_CAPACITY] = 
    "Twinkle, twinkle, little star, how I wonder what you are.\n"
    "Up above the world so high, like a diamond in the sky.\n"
    "Twinkle, twinkle, little star, how I wonder what you are.";
  printf("ORIGINAL STRING\n%s\n", str);
  printf("REVERSED STRING\n%s\n", roy_string_reverse(str));
  printf("REVERSED TO ORIGINAL\n%s", roy_string_reverse(str));
}