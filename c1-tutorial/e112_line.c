#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRING_CAPACITY 1024

char * replace_all(char * str, const char * old_sub, const char * new_sub) {
  int str_len = strlen(str);
  int old_len = strlen(old_sub);
  int new_len = strlen(new_sub);
  int max_len =
    new_len <= old_len ?
    str_len - str_len / str_len * (old_len - new_len) :
    str_len + str_len / old_len * (new_len - old_len);
  // max_len: possibly max length of the string when its done.
  char * temp_str = malloc(max_len + 1);
  // temp_str: buffer string storing the result, 
  // will be freed at the end of the func.
  memset(temp_str, '\0', max_len + 1);
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
    str = match_begin + old_len;
  }
  strcat(temp_str, str);
  strcpy(real_str, temp_str);
  free(temp_str);
  return real_str;
}

int main(void) {
  char str[STRING_CAPACITY] = "Red Orange Yellow Green Blue Indigo Violet";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("\n'Roy G. Biv' STANDS FOR:\n%s\n", replace_all(str, " ", "\n"));
}