#include <stdio.h>

char * strncpy_(char * dest, const char * src, size_t count) {
  char * pdest = dest;
  while ((*pdest++ = *src++) && --count) { }
  return dest;
}

char * strncat_(char * dest, const char * src, size_t count) {
  char * ptail = dest;
  while (*ptail != '\0') { ptail++; }
  strncpy_(ptail, src, count);
  return dest;
}

int strncmp_(const char * str1, const char * str2, size_t count) {
  while (*str1 && *str2 && *str1 == *str2 && count) { 
    str1++;
    str2++;
    count--;
  }
  return *str1 - *str2;
}

int main() {
  enum { STRING_CAPACITY = 256 };
  char str1[STRING_CAPACITY] = "caonima ";
  char str2[STRING_CAPACITY] = "nishishabi";
  puts(strncpy_(str1, str2, STRING_CAPACITY));
}