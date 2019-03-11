#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define STRING_CAPACITY 1024

int count_char(const char * str, int ch) {
  int count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

int count_char_if(const char * str, int (*condition)(int)) {
  int count = 0;
  while (*str != '\0') {
    if (condition(*str++)) {
      count ++;
    }
  }
  return count;
}


int count_str(const char * str, const char * sub) {
  int count = 0;
  const char * pstr = str;
  char * match_begin;
  while (match_begin = strstr(pstr, sub)) {
    count++;
    pstr = match_begin + strlen(sub);
  }
  return count;
}

char * str_tolower(char * str) {
  char * real_str = str;
  while (*str != '\0') {
    *str++ = tolower(*str);
  }
  return real_str;
}

int count_str_insensitive(const char * str, const char * sub) {
  int count = 0;

  char * lower_str = malloc(strlen(str) + 1);
  strcpy(lower_str, str);
  str_tolower(lower_str);
  char * plower_str = lower_str;

  char * lower_sub = malloc(strlen(sub) + 1);
  strcpy(lower_sub, sub);
  str_tolower(lower_sub);
  char * plower_sub = lower_sub;

  char * match_begin;
  while (match_begin = strstr(plower_str, plower_sub)) {
    count++;
    plower_str = match_begin + strlen(plower_sub);
  } 
  free(lower_sub);
  free(lower_str);
  return count;
}

int main(void) {
  char str[STRING_CAPACITY] =
    "\tTo be, or not to be, that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "the slings and arrows of outrageous fortune,\n"
    "Or to take Arms against a Sea of troubles...";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("  NUMBERS OF BLANKS: %d\n", count_char(str, ' '));
  printf("    NUMBERS OF TABS: %d\n", count_char(str, '\t'));
  printf("NUMBERS OF NEWLINES: %d\n", count_char(str, '\n'));
  printf("        SPACE TOTAL: %d\n", count_char_if(str, isspace));
  printf("    NUMBERS OF 'to': %d\n", count_str(str, "to"));
  printf(" NUMBERS OF 'To/to': %d\n", count_str_insensitive(str, "to"));

}