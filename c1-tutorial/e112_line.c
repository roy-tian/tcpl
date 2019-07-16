#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

enum {
  STRING_CAPACITY = 1023
};

char *
replaceAllChar(char * str,
               int    old_ch,
               int    new_ch) {
  char * pstr = str;
  while (*pstr != '\0') {
    if (*pstr == old_ch) {
      *pstr = new_ch;
    }
    pstr++;
  }
  return str;
}

char *
replaceAllCharIf(char * str,
                 int (* condition)(int),
                 int    new_ch) {
  char * pstr = str;
  while (*pstr != '\0') {
    if (condition(*pstr)) {
      *pstr = new_ch;
    }
    pstr++;
  }
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] = "Red Orange Yellow Green Blue Indigo Violet";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("\n'Roy G. Biv' STANDS FOR:\n%s\n",
         replaceAllChar(str, ' ', '\n'));

  strcpy(str, "Red,Orange.Yellow;Green|Blue:Indigo!Violet?");
  printf("\nORIGINAL STRING:\n%s\n", str);
  printf("\n'Roy G. Biv' STANDS FOR:\n%s\n",
         replaceAllCharIf(str, ispunct, '\n'));
}