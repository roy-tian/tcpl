#include <stdio.h>
#include <string.h>
#include <ctype.h>

void str_toupper(char * str) {
  char * pstr = str;
  while (*pstr) {
    *pstr = toupper(*pstr);
    pstr++;
  }
}

void str_tolower(char * str) {
  char * pstr = str;
  while (*pstr) {
    *pstr = tolower(*pstr);
    pstr++;
  }
}

int main(int argc, char ** argv) {
  if (strstr(argv[0], "upper")) {
    for (int i = 1; i < argc; i++) {
      str_toupper(argv[i]);
    }
  } else if (strstr(argv[0], "lower")) {
    for (int i = 1; i < argc; i++) {
      str_tolower(argv[i]);
    }
  }
  for (int i = 1; i < argc; i++) {
    puts(argv[i]);
  }
}