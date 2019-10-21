#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

enum {
  STRING_CAPACITY = 1023
};

char *
stringToLower(char * str) {
  char * pStr = str;
  while ((*pStr = tolower(*pStr)) != '\0') {
    pStr++;
  }
  return str;
}

size_t
countChar(const char * str,
          int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count++;
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
  const char * pStr;
  const char * pSub;
  char lowerStr[STRING_CAPACITY + 1] = "\0";
  char lowerSub[STRING_CAPACITY + 1] = "\0";

  if (sensibility) {
    pStr = str;
    pSub = sub;
  } else {
    strcpy(lowerStr, str);
    stringToLower(lowerStr);
    pStr = lowerStr;

    strcpy(lowerSub, sub);
    stringToLower(lowerSub);
    pSub = lowerSub;
  }

  char * pMatchBegin;
  while ((pMatchBegin = strstr(pStr, pSub))) {
    count++;
    pStr = pMatchBegin + strlen(pSub);
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