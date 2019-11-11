#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 1023
};

char *
replaceAll(char       * str,
           const char * oldSub,
           const char * newSub) {
  char tempStr[STRING_CAPACITY + 1] = "\0";
  char * pTempStr = tempStr;
  char * pStr = str;
  char * pMatchBegin;
  while ((pMatchBegin = strstr(pStr, oldSub))) {
    strncat(pTempStr, pStr, pMatchBegin - pStr);
    strcat(pTempStr, newSub);
    pStr = pMatchBegin + strlen(oldSub);
  }
  strcat(tempStr, pStr);
  strcpy(str, tempStr);
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] =
    "Let freedom ring from the mighty mountains of New York.\n"
    "Let	freedom	ring	from	the	heightening	Alleghenies	of	Pennsylvania.\n"
    "Let freedom ring from the snow-capped Rockies of Colorado.\n"
    "Let freedom ring from the curvaceous slopes of California.\n";

  printf("ORIGINAL STRING:\n%s\n", str);
  replaceAll(str, "	", "\\t");
  replaceAll(str, "\n", "\\n\n");
  printf("RESULT STRING:\n%s\n", str);
  replaceAll(str, "\\n\n", "\n");
  replaceAll(str, "\\t", "	");
  printf("REPLACE REVERSELY:\n%s\n", str);
}