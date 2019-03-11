#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRING_CAPACITY 1024

char * replace_all(char * str, const char * old_sub, const char * new_sub) {
  int max_len =
    strlen(new_sub) <= strlen(old_sub) ?
    strlen(str) :
    strlen(str) +
    strlen(str) / strlen(old_sub) * (strlen(new_sub) - strlen(old_sub));
  // max_len: possibly max length of the string when its done.
  char * temp_str = malloc(max_len);
  // temp_str: buffer string storing the result, 
  // will be freed at the end of the func.
  memset(temp_str, '\0', max_len);
  // strings should always be initialized.
  char * ptemp_str = temp_str;
  // ptemp_str: just a pointer to the string.
  char * real_str = str;
  // real_str: stores the address of 'str',
  // to be returned. 
  char * match_begin;
  // points to the beginning of a matched sub.
  while (match_begin = strstr(str, old_sub)) {
    strncat(ptemp_str, str, match_begin - str);
    strcat(ptemp_str, new_sub);
    str = match_begin;
    str += strlen(old_sub);
  }
  strcat(temp_str, str);
  strcpy(real_str, temp_str);
  free(temp_str);
  return real_str;
}

int main(void) {
  char str[STRING_CAPACITY] = 
    "Let freedom ring from the mighty mountains of New York.\n"
    "Let	freedom	ring	from	the	heightening	Alleghenies	of	Pennsylvania.\n"
    "Let freedom ring from the snow-capped Rockies of Colorado.\n"
    "Let freedom ring from the curvaceous slopes of California.\n";
  printf("ORIGINAL STRING:\n%s\n", str);
  replace_all(str, "	", "\\t");
  replace_all(str, "\n", "\\n\n");
  printf("RESULT STRING:\n%s\n", str);
  replace_all(str, "\\n\n", "\n");
  replace_all(str, "\\t", " ");
  printf("REPLACE REVERSELY:\n%s\n", str);
}