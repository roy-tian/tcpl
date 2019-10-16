#include <stdio.h>
#include <string.h>

enum {
  STRING_CAPACITY = 1023,
};

char * fillChar(char * dest, int ch, size_t count);
char * replaceIndex(char * str, size_t oldSubPosition, size_t oldSubLength, const char * newSub);
char * detab(char * str, size_t tabSize);

char *
fillChar(char * dest,
         int    ch,
         size_t count) {
  size_t i = 0;
  for (; i != count; i++) {
    *(dest + i) = ch;
  }
  *(dest + i) = '\0';
  return dest;
}

char *
replaceIndex(char       * str,
             size_t       oldSubPosition,
             size_t       oldSubLength,
             const char * newSub) {
  char tempStr[STRING_CAPACITY + 1] = "\0";
  strncpy(tempStr, str, oldSubPosition);
  strcat(tempStr, newSub);
  strcat(tempStr, str + oldSubPosition + oldSubLength);
  strcpy(str, tempStr);
  return str;
}

char * detab(char * str, size_t tabSize) {
  char * pStr = str;
  size_t tabMarker = 0;
  while (*pStr != '\0') {
    if (*pStr == '\t') {
      char repeatStr[STRING_CAPACITY + 1] = "\0";
      size_t repeatCount = tabSize - tabMarker % tabSize;
      fillChar(repeatStr, ' ', repeatCount);
      replaceIndex(str, pStr - str, 1, repeatStr);
      tabMarker += repeatCount - 1;
      pStr += repeatCount - 1;
    } else if (*pStr == '\n') {
      tabMarker = 0;
      pStr++;
    } else {
      tabMarker++;
      pStr++;
    }
  }
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] = 
    "Fly,\tfly,\tfly\tyour\tkite,\n"
    "High  \t  in   \tthe\t sky;\t\n"
    "\t  \t \t\n"
    "\tUp and \t\t down,\n"
    "   \tRound and round,\n"
    "Let \tyour\t kite fly high.";
  FILE * fp = fopen("e120.txt", "w+");
  fputs("ORIGINAL STRING\n=============\n", fp);
  fputs(str, fp);
  fputs("\n\nDETABED STRING\n============\n", fp);
  fputs(detab(str, 8), fp);
  fclose(fp);
}
