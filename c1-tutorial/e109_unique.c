#include <stdio.h>
#include "roystring.h"
#define STRING_CAPACITY 1024

int main(void) {
  char str[STRING_CAPACITY] = 
    "Winning that ticket, Rose, was the best thing that ever happened to me...\n"
    "it brought me to you.     And I’m thankful for that, Rose. I’m thankful.\n"
    "You must do me this      honor.      You must promise me you’ll survive.\n"
    "That you won’t give up,  no matter what happens, no matter how hopeless.\n"
    "Promise me now,          Rose,         and never let go of that promise.\m";
  printf("ORIGINAL STRING:\n%s\n", str);
  printf("RESULT STRING:\n%s\n", roy_string_unique_char(str, ' '));
}