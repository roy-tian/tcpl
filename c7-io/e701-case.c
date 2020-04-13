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
  void (*func)(char * str) = NULL;
  if (strstr(argv[0], "upper")) {
    func = str_toupper;
  } else if (strstr(argv[0], "lower")) {
    func = str_tolower;
  }
  for (int i = 1; i < argc; i++) {
    func ? func(argv[i]) : NULL;
    puts(argv[i]);
  }
}