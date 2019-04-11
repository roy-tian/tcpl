#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_sequence(char * dest, int front_ch, int back_ch) {
  char * pdest = dest;
  while (front_ch <= back_ch) {
    *pdest++ = front_ch++;
  }
  *pdest = '\0';
  return dest;
}

char * roy_string_fill_sequence(char * dest, const char * pattern) {
  int flag = 0;
  char * pdest = dest;
  while (*pattern != '\0') {
    if (flag == 0 && isprint(*pattern)) {
      flag++;
    } else if (flag == 1 && *pattern == '-') {
      flag++;
    } else if (flag == 2 && isprint(*pattern)) {
      ROY_STRING(buf, STRING_CAPACITY)
      strcat(dest, roy_string_sequence(buf, *(pattern - 2), *pattern));
      pdest += strlen(buf);
      flag = 0;
    } else if (flag == 1 && isprint(*pattern)) {
      *pdest++ = *(pattern - 1);
      flag = 1;
    }
    pattern++;
  }
  
  if (flag == 2) {
    *pdest++ = *(pattern - 2);
    *pdest++ = *(pattern - 1);
  }
  if (flag == 1) {
    *pdest++ = *(pattern - 1);
  }
  *pdest = '\0';
  return dest;
}

int main(void) {
  ROY_STRING(buf, STRING_CAPACITY)
  puts(roy_string_fill_sequence(buf, "-a----z1-9-"));
}