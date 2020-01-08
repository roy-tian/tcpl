#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *
unique(char * str,
       int    ch) {
  // tempStr: a temporary-stored string.
  // Undefined behaviors would occur if str grows out of its capacity.
  char tempStr[strlen(str) + 1];
  *tempStr = '\0';
  // a pointer to the real tempStr.
  char * pTempStr = tempStr;
  // a pointer to the real str.
  char * pStr = str;
  // stand when the first 'ch' is tracked, lay down when repeating 'ch's end.
  bool flag = false;
  while (*pStr != '\0') {
    if (!flag && *pStr == ch) {
      flag = true;
      *pTempStr++ = *pStr++;
    } else if (!flag && *pStr != ch) {
      *pTempStr++ = *pStr++;
    } else if (flag && *pStr == ch) {
      pStr++;
    } else { // (flag && *src != ch)
      flag = false;
      *pTempStr++ = *pStr++;
    }
  }
  strcpy(str, tempStr);
  return str;
}

int main(void) {
  char str[] =
    "Winning that ticket, Rose, was the best thing that ever happened to me...\n"
    "it brought me to you.     And I'm thankful for that, Rose. I'm thankful.\n"
    "You must do me this      honor.      You must promise me you'll survive.\n"
    "That you won't give up,  no matter what happens, no matter how hopeless.\n"
    "Promise me now,          Rose,         and never let go of that promise.\n";
  puts("ORIGINAL STRING:");
  puts(str);
  puts("RESULT STRING:");
  puts(unique(str, ' '));
}