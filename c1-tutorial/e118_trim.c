#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 1023
};

size_t countChar(const char * str, int ch);
size_t countLine(const char * str);
char * lineContent(char * lineContent, const char * str, size_t lineNumber);
char * trimLine(char * str);
char * trim(char * str);

size_t
countChar(const char * str,
          int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t
countLine(const char * str) {
  size_t count = countChar(str, '\n');
  size_t strLength = strlen(str);
  if (strLength != 0 && *(str + strLength - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

char *
lineContent(char       * lineContent,
            const char * str,
            size_t       lineNumber) {
  while ((lineNumber-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * strTail = strchr(str, '\n');
  if (!strTail) {
    strcpy(lineContent, str);
  } else {
    strncpy(lineContent, str, strTail - str);
  }
  return lineContent;
}

char *
trimLine(char * str) {
  char * pStrTail = str + strlen(str);
  while (str < pStrTail && isblank(*(pStrTail - 1))) {
    pStrTail--;
  }
  *pStrTail = '\0';
  return str;
}

char *
trim(char * str) {
  char tempStr[STRING_CAPACITY + 1] = "\0";
  for (int i = 1; i <= countLine(str); i++) {
    char curLine[STRING_CAPACITY + 1] = "\0";
    lineContent(curLine, str, i);
    trimLine(curLine);
    if (strlen(curLine) != 0) { 
      strcat(tempStr, "\n");
      strcat(tempStr, curLine);
    }
  }
  strcpy(str, tempStr + 1);
  return str;
}

int main(void) {
  char str[] =
    "#include <iostream>    \n"
    "\n"
    "int main(int argc, char * argv[]) { \t          \n"
    "\tstd::cout << \"Hello world\"    \t    \n"
    "\t\t  << std::endl;      \t\n"
    "\t\n"
    "}"
    "   \n\t\n\n\n   \n\n\n    ";
  FILE * fp = fopen("e118.txt", "w+");
  fputs("ORIGINAL CODE\n=============\n", fp);
  fputs(str, fp);
  fputs("\nTRIMMED CODE\n============\n", fp);
  fputs(trim(str), fp);
  fclose(fp);
}