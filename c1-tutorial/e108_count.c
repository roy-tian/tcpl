#include <stdio.h>
#include <ctype.h>
#define STRING_CAPACITY 1024

int count(const char * restrict str, int ch) {
  int count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

int countif(const char * restrict str, int (*condition)(int)) {
  int count = 0;
  while (*str != '\0') {
    if (condition(*str++)) {
      count ++;
    }
  }
  return count;
}

int main(void) {
  char str[STRING_CAPACITY] = "\tTo be, or not to be, that is the question:\n"
                              "Whether 'tis nobler in the mind to suffer\n"
                              "the slings and arrows of outrageous fortune,\n"
                              "Or to take Arms against a Sea of troubles...";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("NUMBERS OF BLANKS:%5d\n",   count(str, ' '));
  printf("NUMBERS OF TABS:%6d\n",     count(str, '\t'));
  printf("NUMBERS OF NEWLINES:%2d\n", count(str, '\n'));
  printf("TOTAL:%17d\n",              countif(str, isspace));
}