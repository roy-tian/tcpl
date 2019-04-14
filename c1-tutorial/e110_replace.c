#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_replace_all(char * str,
                              const char * old_sub,
                              const char * new_sub) {
  // temp_str: a temporary-stored string.
  // Undefined behaviors would occur if str grows out of its capacity.
  ROY_STRING(temp_str, strlen(str))
  // a pointer to the real temp_str.
  char * ptemp_str = temp_str;
  // a pointer to the real str.
  char * pstr;
  // a pointer to the beginning of a matched substring.
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
  roy_string_replace_all(str, "	", "\\t");
  roy_string_replace_all(str, "\n", "\\n\n");
  printf("RESULT STRING:\n%s\n", str);
  roy_string_replace_all(str, "\\n\n", "\n");
  roy_string_replace_all(str, "\\t", "	");
  printf("REPLACE REVERSELY:\n%s\n", str);
}