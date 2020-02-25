#include <stdio.h>
#include <string.h>

enum { BUFFER_SIZE = 1024 };

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
entab(char   * str,
      size_t   tabSize) {
  char * pStr = str;
  size_t pos = 1;
  while (*pStr != '\0') {
    if (*pStr == ' ' && pos % tabSize == 0) {
      char * pBlank = pStr;
      while (*pBlank == ' ') {
        pBlank--;
      }
      replaceIndex(str, pBlank - str + 1, pStr - pBlank, "\t");
      pos += pStr - pBlank - 1;
    }
    pos = (*++pStr == '\n' ? 0 : ++pos);
  }
  return str;
}

int main(void) {
  char str[] =
    "def ask_ok(prompt, retries = 4, reminder = 'Please try again!'):\n"
    "while True:\n"
    "    ok = input(prompt)\n"
    "    if ok in ('y', 'ye', 'yes'):          \t        \n"
    "        return   True\n"
    "    if ok in ('n', 'no', 'nop', 'nope'):\t         \t\n"
    "        return   False\n"
    "    retries = retries - 1\n"
    "    if retries < 0:\n"
    "        raise\tValueError('invalid user response')\n"
    "    print(reminder)";
  FILE * fp = fopen("e121.py", "w+");
  fputs("#ORIGINAL CODE:\n", fp);
  fputs(str, fp);
  fputs("\n\n#AFTER ENTAB:\n", fp);
  fputs(entab(str, 4), fp);
  fclose(fp);
}
