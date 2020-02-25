#include <stdio.h>
#include <string.h>

enum { BUFFER_SIZE = 1024, };

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
  char tempStr[BUFFER_SIZE] = "\0";
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
      char repeatStr[BUFFER_SIZE] = "\0";
      size_t repeatCount = tabSize - tabMarker % tabSize;
      fillChar(repeatStr, ' ', repeatCount);
      replaceIndex(str, pStr - str, 1, repeatStr);
      tabMarker += repeatCount - 1;
      pStr += repeatCount - 1;
    } else {
      tabMarker = (*pStr == '\n' ? 0 : ++tabMarker);
      pStr++;
    }
  }
  return str;
}

int main(void) {
  char str[] = 
    "Fly,\tfly,\tfly\tyour\tkite,\n"
    "High  \t  in   \tthe\t sky;\t\n"
    "\t  \t \t\n"
    "\tUp and \t\t down,\n"
    "   \tRound and round,\n"
    "Let \tyour\t kite fly high.";
  FILE * fp = fopen("e120.txt", "w+");
  fputs("ORIGINAL STRING:\n----------------\n", fp);
  fputs(str, fp);
  fputs("\n\nDETABED STRING:\n---------------\n", fp);
  fputs(detab(str, 8), fp);
  fclose(fp);
}
