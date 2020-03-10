#include <stdio.h>

enum { BUFFER_SIZE = 128 };

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
  while ( *str1 && (*str1 == *str2) && count ) { 
    str1++;
    str2++;
    count--;
  }
  return *str1 - *str2;
}

int main(void) {
  char str1[BUFFER_SIZE] = "I'm gonna make him ";
  char str2[BUFFER_SIZE] = "an offer he can\'t refuse.";
  char str3[BUFFER_SIZE] = "\0";
  puts(strncat_(str1, str2, BUFFER_SIZE));
  puts(strncpy_(str3, str1, BUFFER_SIZE));
  puts(strncpy_(str3, str1, 19));
  printf("%d ", strncmp_(str1, str3, BUFFER_SIZE));
  printf("%d\n", strncmp_(str1, str3, 18));
}