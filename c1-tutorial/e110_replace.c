#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 1023
};

char *
replaceAll(char       * str,
           const char * old_sub,
           const char * new_sub) {
  char temp_str[STRING_CAPACITY + 1] = "\0";
  char * ptemp_str = temp_str;
  char * pstr;
  pstr = str;
  char * pmatch_begin;
  while ((pmatch_begin = strstr(pstr, old_sub))) {
    strncat(ptemp_str, pstr, pmatch_begin - pstr);
    strcat(ptemp_str, new_sub);
    pstr = pmatch_begin + strlen(old_sub);
  }
  strcat(temp_str, pstr);
  strcpy(str, temp_str);
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