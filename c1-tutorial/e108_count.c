#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

enum {
  STRING_CAPACITY = 1023
};

char *
stringToLower(char * str) {
  char * pstr = str;
  while ((*pstr = tolower(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

size_t
countChar(const char * str,
          int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t
countCharIf(const char * str,
            int       (* condition)(int)) {
  size_t count = 0;
  while (*str != '\0') {
    if (condition(*str++)) {
      count++;
    }
  }
  return count;
}

size_t
countSub(const char * str,
         const char * sub,
         bool         sensibility) {
  size_t count = 0;
  const char * pstr;
  const char * psub;
  char lower_str[STRING_CAPACITY + 1] = "\0";
  char lower_sub[STRING_CAPACITY + 1] = "\0";

  if (sensibility) {
    pstr = str;
    psub = sub;
  } else {
    strcpy(lower_str, str);
    stringToLower(lower_str);
    pstr = lower_str;

    strcpy(lower_sub, sub);
    stringToLower(lower_sub);
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
  printf("\nNUMBER OF:\n");
  printf("  BLANKS: %zu\n", countChar(str, ' '));
  printf("    TABS: %zu\n", countChar(str, '\t'));
  printf("NEWLINES: %zu\n", countChar(str, '\n'));
  printf("  SPACES: %zu\n", countCharIf(str, isspace));
  printf("   'to's: %zu\n", countSub(str, "to", true));
  printf("'To/to's: %zu\n", countSub(str, "to", false));
}