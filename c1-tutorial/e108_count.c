#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

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
         const char * sub) {
  size_t count = 0;
  char * pMatchBegin;
  while ((pMatchBegin = strstr(str, sub))) {
    count++;
    str = pMatchBegin + strlen(sub);
  } 
  return count;
}

char *
stringToLower(char * str) {
  char * pStr = str;
  while ((*pStr = tolower(*pStr)) != '\0') {
    pStr++;
  }
  return str;
}

size_t
countSubI(const char * str,
          const char * sub) {
  char lowerStr[strlen(str) + 1];
  strcpy(lowerStr, str);
  stringToLower(lowerStr);
  str = lowerStr;

  char lowerSub[strlen(sub) + 1];
  strcpy(lowerSub, sub);
  stringToLower(lowerSub);
  sub = lowerSub;

  char * pMatchBegin;
  size_t count = 0;
  while ((pMatchBegin = strstr(str, sub))) {
    count++;
    str = pMatchBegin + strlen(sub);
  } 
  return count;
}

int main(void) {
  const char str[] =
    "\tTo be, or not to be, that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "the slings and arrows of outrageous fortune,\n"
    "Or to take Arms against a Sea of troubles...";

  printf("ORIGINAL STRING:\n%s\n", str);
  printf("\nSTATS:\n");
  printf("  BLANKS: %zu\n", countChar(str, ' '));
  printf("    TABS: %zu\n", countChar(str, '\t'));
  printf("NEWLINES: %zu\n", countChar(str, '\n'));
  printf("  SPACES: %zu\n", countCharIf(str, isspace));
  printf("   'to's: %zu\n", countSub(str, "to"));
  printf("'To/to's: %zu\n", countSubI(str, "to"));
}