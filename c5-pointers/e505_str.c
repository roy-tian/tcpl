#include <stdio.h>

char * strncpy_(char * dest, const char * src, size_t count) {
  char * pdest = dest;
  while ((*pdest++ = *src++) && --count) { }
  *pdest = '\0';
  return dest;
}

char * strncat_(char * dest, const char * src, size_t count) {
  char * ptail = dest;
  while (*ptail != '\0') { ptail++; }
  strncpy_(ptail, src, count);
  return dest;
}

int strncmp_(const char * str1, const char * str2, size_t count) {
  while (*str1 && *str1 == *str2 && count) { 
    str1++;
    str2++;
    count--;
  }
  return *str1 - *str2;
}

int main(void) {
  enum { STRING_CAPACITY = 256 };
  char str1[STRING_CAPACITY] = "I'm gonna make him ";
  char str2[STRING_CAPACITY] = "an offer he can\'t refuse.";
  char str3[STRING_CAPACITY];
  puts(strncat_(str1, str2, STRING_CAPACITY));
  puts(strncpy_(str3, str1, STRING_CAPACITY));
  puts(strncpy_(str3, str1, 19));
  printf("%d ", strncmp_(str1, str3, STRING_CAPACITY));
  printf("%d", strncmp_(str1, str3, 18));
}