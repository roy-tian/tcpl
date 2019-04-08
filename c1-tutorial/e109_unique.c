#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_unique_char(char * str, int ch);

char * roy_string_unique_char(char * str, int ch) {
  // temp_str: a temporary-stored string.
  ROY_STRING(temp_str, strlen(str))
  // a pointer to the real temp_str.
  char * ptemp_str = temp_str;
  // a pointer to the real str.
  char * pstr = str;
  // stand when the first 'ch' is tracked, lay down when repeating 'ch's end.
  bool flag = false;
  while (*pstr != '\0') {
    if (!flag && *pstr == ch) {
      flag = true;
      *ptemp_str++ = *pstr++;
    } else if (!flag && *pstr != ch) {
      *ptemp_str++ = *pstr++;
    } else if (flag && *pstr == ch) {
      pstr++;
    } else { // (flag && *src != ch)
      flag = false;
      *ptemp_str++ = *pstr++;
    }
  }
  strcpy(str, temp_str);
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] = 
    "Winning that ticket, Rose, was the best thing that ever happened to me...\n"
    "it brought me to you.     And I’m thankful for that, Rose. I’m thankful.\n"
    "You must do me this      honor.      You must promise me you’ll survive.\n"
    "That you won’t give up,  no matter what happens, no matter how hopeless.\n"
    "Promise me now,          Rose,         and never let go of that promise.\n";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("RESULT STRING:\n%s\n", roy_string_unique_char(str, ' '));
}