#include <stdio.h>
#include <string.h>

int roy_string_substring_index(const char * str, const char * sub) {
  int i_str = 0, i_str_cur, i_sub;
  while (*(str + i_str) != '\0') {
    i_str_cur = i_str;
    i_sub = 0;
    while (*(sub + i_sub) != '\0' &&
           *(str + i_str_cur) == *(sub + i_sub)) {
      i_str_cur++;
      i_sub++;
    }
    if (i_sub != 0 && *(sub + i_sub) == '\0') {
      return i_str;
    }
    i_str++;
  }
  return -1;
}

int roy_string_substring_reverse_index(const char * str, const char * sub) {
  int ri_str = strlen(str) - 1;
  int ri_str_cur, ri_sub;
  while (ri_str >= 0) {
    ri_str_cur = ri_str;
    ri_sub = strlen(sub) - 1;
    while (ri_sub >= 0 && *(str + ri_str_cur) == *(sub + ri_sub)) {
      ri_str_cur--;
      ri_sub--;
    }
    if (ri_sub == -1) {
      return ri_str - strlen(sub) + 1;
    }
    ri_str--;
  }
  return -1;
}

int main(void) {
  const char * str = "The bookkeeper keeps the books from being broke.";
  const char * sub = "keep";
  printf(" INDEX: %d\n", roy_string_substring_index(str, sub));
  printf("RINDEX: %d\n", roy_string_substring_reverse_index(str, sub));
}