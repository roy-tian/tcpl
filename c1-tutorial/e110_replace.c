#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *
replaceAll(char       * str,
           const char * oldSub,
           const char * newSub) {
  char buf[strlen(str) * 2]; // the length of 'buf' is a trade-off.
  memset(buf, '\0', strlen(buf));
  char * pBuf = buf;
  char * pStr = str;
  char * pMatch;
  while ((pMatch = strstr(pStr, oldSub))) {
    strncat(pBuf, pStr, pMatch - pStr);
    strcat(pBuf, newSub);
    pStr = pMatch + strlen(oldSub);
  }
  strcat(buf, pStr);
  strcpy(str, buf);
  return str;
}

int main(void) {
  char str[] =
    "Let freedom ring from the mighty mountains of New York.\n"
    "Let	freedom	ring	from	the	heightening	Alleghenies	of	Pennsylvania.\n"
    "Let freedom ring from the snow-capped Rockies of Colorado.\n"
    "Let freedom ring from the curvaceous slopes of California.\n";

  puts("ORIGINAL STRING:");
  puts(str);
  replaceAll(str, "	", "\\t");
  replaceAll(str, "\n", "\\n\n");
  puts("RESULT STRING:");
  puts(str);
  replaceAll(str, "\\n\n", "\n");
  replaceAll(str, "\\t", "	");
  puts("REPLACE REVERSELY:");
  puts(str);
}