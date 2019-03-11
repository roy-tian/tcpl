#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRING_CAPACITY 1024

char * unique(char * str, int ch) {
  char * temp_str = malloc(strlen(str) + 1);
  // temp_str: buffer string storing the result, 
  // will be freed at the end of the func.
  memset(temp_str, '\0', strlen(str) + 1);
  // strings should always be initialized.
  char * ptemp_str = temp_str;
  // ptemp_str: just a pointer to the string.
  char * real_str = str;
  // real_str: stores the address of 'str',
  // to be returned. 
  bool flag = false;  
  while (*str != '\0') {
    if (!flag && *str == ch) {
      flag = true;
      *ptemp_str++ = *str++;
    } else if (!flag && *str != ch) {
      *ptemp_str++ = *str++;
    } else if (flag && *str == ch) {
      str++;
    } else { // (flag && *src != ch)
      flag = false;
      *ptemp_str++ = *str++;
    }
  }
  strcpy(real_str, temp_str);
  free(temp_str);
  return real_str;
}

int main(void) {
  char str[STRING_CAPACITY] = 
    "Winning that ticket, Rose, was the best thing that ever happened to me...\n"
    "it brought me to you.     And I’m thankful for that, Rose. I’m thankful.\n"
    "You must do me this      honor.      You must promise me you’ll survive.\n"
    "That you won’t give up,  no matter what happens, no matter how hopeless.\n"
    "Promise me now,          Rose,         and never let go of that promise.\n";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("RESULT STRING:\n%s\n", unique(str, ' '));
}