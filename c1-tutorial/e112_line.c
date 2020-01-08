#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *
replaceAllChar(char * str,
               int    oldCh,
               int    newCh) {
  char * pStr = str;
  while (*pStr != '\0') {
    if (*pStr == oldCh) {
      *pStr = newCh;
    }
    pStr++;
  }
  return str;
}

char *
replaceAllCharIf(char * str,
                 int (* condition)(int),
                 int    newCh) {
  char * pStr = str;
  while (*pStr != '\0') {
    if (condition(*pStr)) {
      *pStr = newCh;
    }
    pStr++;
  }
  return str;
}

int main(void) {
  char str1[] = "Red Orange Yellow Green Blue Indigo Violet";
  puts("ORIGINAL STRING:");
  puts(str1);
  puts("'Roy G. Biv' STANDS FOR:");
  puts(replaceAllChar(str1, ' ', '\n'));

  char str2[] = "Red,Orange.Yellow;Green|Blue:Indigo!Violet";
  puts("\nORIGINAL STRING:");
  puts(str2);
  puts("'Roy G. Biv' STANDS FOR:");
  puts(replaceAllCharIf(str2, ispunct, '\n'));
}