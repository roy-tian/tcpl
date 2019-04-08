#include <stdio.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

int get_line(char * dest, int max_length) {
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

int get_line_without_and(char * dest, int max_length) {
  int i = 0, ch = getchar();
  for (; (i < max_length - 1) + (ch != '\n') + (ch != EOF) == 3; i++) {
    dest[i] = ch;
    ch = getchar();
  }
  if (ch == '\n') {
    dest[i++] = ch;
  }
  dest[i] = '\0';
  return i;
}

int get_line_without_for(char * dest, int max_length) {
  int count = 0, ch = getchar();
  while (ch != EOF) {
    if (count >= max_length - 1) {
      break;
    }
    if (ch == '\n') {
      dest[count++] = ch;
      break;
    }
    dest[count++] = ch;
    ch = getchar();
  }
  dest[count] = '\0';
  return count;
}

int main(void) {
  ROY_STRING(str, STRING_CAPACITY);
  int len = get_line_without_for(str, 80);
  printf("%d\n%s", len, str);
}