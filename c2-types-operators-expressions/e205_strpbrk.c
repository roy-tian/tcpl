#include <stdio.h>
#include <string.h>

int roy_string_break_index(const char * str, const char * set) {
  int pos = 0;
  while (*(str + pos) != '\0' && !strchr(set, *(str + pos))) {
    pos++;
  }
  return pos;
}

int main(void) {
  char * str = "Le français est la plus belle langue du monde.";
  printf("%s %zu", str, roy_string_break_index(str, "le"));
}