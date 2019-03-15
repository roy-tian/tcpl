#include <stdio.h>
#include <ctype.h>
#include "roystring.h"

#define STRING_CAPACITY 1024

int main(void) {
  char str[STRING_CAPACITY] =
    "\tTo be, or not to be, that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "the slings and arrows of outrageous fortune,\n"
    "Or to take Arms against a Sea of troubles...";

  printf("ORIGINAL STRING:\n%s\n", str);
  printf("   NUMBER OF BLANKS: %d\n", roy_string_count_char(str, ' '));
  printf("     NUMBER OF TABS: %d\n", roy_string_count_char(str, '\t'));
  printf(" NUMBER OF NEWLINES: %d\n", roy_string_count_char(str, '\n'));
  printf("        SPACE TOTAL: %d\n", roy_string_count_char_if(str, isspace));
  printf("    NUMBER OF 'to's: %d\n", roy_string_count_substring(str, "to", true));
  printf(" NUMBER OF 'To/to's: %d\n", roy_string_count_substring(str, "to", false));
  

}