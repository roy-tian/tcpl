#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum { BUFFER_SIZE = 4096 };

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

char *
replaceBetween(char       * str,
               const char * patternHead,
               const char * patternTail,
               const char * newSub) {
  char * pHead = str;
  bool flag = false;
  while ((pHead = strstr(str, patternHead))) {
    if (flag == true) {
      char * pTail = strstr(pHead, patternTail);
      replaceIndex(str,
                   pHead - str,
                   pTail - pHead + strlen(patternTail),
                   newSub);
      flag = false;  
    } else {
      flag = true;
    }
  }
  return str;
}

char * decomment(char * str) {
  replaceBetween(str, "/*", "*/", "");
  replaceBetween(str, "//", "\n", "");
  return str;
}

char * readFromFile(char * dest, const char * path) {
  FILE * fp = fopen(path, "r");

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  fread(dest, sizeof(char), size, fp);
  dest[size] = '\0';
  fclose(fp);
  return dest;
}

int appendToFile(const char * src, const char * path) {
  FILE * fp = fopen(path, "a+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}

int main() {
  char str[BUFFER_SIZE] = "\0";
  readFromFile(str, "e123.java");
  decomment(str);
  appendToFile(str, "e123dc.java");
}