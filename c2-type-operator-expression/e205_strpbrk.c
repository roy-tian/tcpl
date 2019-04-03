#include "roystring.h"
#include <stdio.h>

int main(void) {
  char * str = "Le français est la plus belle langue du monde.";
  printf("%s %zu", str, roy_string_break_index(str, "le"));
}