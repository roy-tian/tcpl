#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_to_lower(char * str) {
  char * pstr = str;
  while ((*pstr = tolower(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

size_t roy_string_count_char(const char * str, int ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t roy_string_count_char_if(const char * str, int (*condition)(int)) {
  size_t count = 0;
  while (*str != '\0') {
    if (condition(*str++)) {
      count++;
    }
  }
  return count;
}

size_t roy_string_count_substring(const char * str,
                                  const char * sub,
                                  bool sensibility) {
  size_t count = 0;
  const char * pstr;
  const char * psub;
  ROY_STRING(lower_str, strlen(str))
  ROY_STRING(lower_sub, strlen(sub))

  if (sensibility) {
    pstr = str;
    psub = sub;
  } else {
    strcpy(lower_str, str);
    roy_string_to_lower(lower_str);
    pstr = lower_str;

    strcpy(lower_sub, sub);
    roy_string_to_lower(lower_sub);
    psub = lower_sub;
  }

  char * pmatch_begin;
  while ((pmatch_begin = strstr(pstr, psub))) {
    count++;
    pstr = pmatch_begin + strlen(psub);
  } 
  return count;
}


int main(void) {
  char str[STRING_CAPACITY + 1] =
    "\tTo be, or not to be, that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "the slings and arrows of outrageous fortune,\n"
    "Or to take Arms against a Sea of troubles...";

  printf("ORIGINAL STRING:\n%s\n", str);
  printf("   NUMBER OF BLANKS: %zu\n", roy_string_count_char(str, ' '));
  printf("     NUMBER OF TABS: %zu\n", roy_string_count_char(str, '\t'));
  printf(" NUMBER OF NEWLINES: %zu\n", roy_string_count_char(str, '\n'));
  printf("        SPACE TOTAL: %zu\n", roy_string_count_char_if(str, isspace));
  printf("    NUMBER OF 'to's: %zu\n", roy_string_count_substring(str, "to", true));
  printf(" NUMBER OF 'To/to's: %zu\n", roy_string_count_substring(str, "to", false));
}