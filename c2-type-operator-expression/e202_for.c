#include <stdio.h>
#include "../roystring.h"

int getline(char * dest, int max_length) {
  int i = 0, ch;
  for (; i < max_length - 1 && (ch = getchar()) != '\n' && ch != EOF; i++) {
    dest[i] = ch;
  }
  if (ch == '\n') {
    dest[i] = ch;
    i++;
  }
  dest[i] = '\0';
  return i;
}

int main(void) {
  ROY_STRING(str, STRING_CAPACITY);
  int len = getline(str, 80);
  printf("%d\n%s", len, str);
}