#include <stdio.h>
#include "roystring.h"

#define STRING_CAPACITY 1024

int main(void) {
  char str[STRING_CAPACITY] =
    "I have a cat,\n"
    "Its name is Tit;\n"
    "And by this fire\n"
    "It Loves to sit.\n"
    "\n"
    "From off the rug\n"
    "It scarce will stir,\n"
    "But there will sit\n"
    "All day and purr.\n"
    "\n"
    "Each day I bring\n"
    "Its dish of milk,\n"
    "And smooth its coat\n"
    "To shine like silk.\n"
    "\n"
    "And on my knee\n"
    "It oft will sit;\n"
    "And I love it.";
  int max_length = 0, max_line = 1;
  for (int i = 1; i <= roy_string_count_line(str); i++) {
    int cur_length = roy_string_line_length(str, i);
    if (cur_length > max_length) {
      max_length = cur_length;
      max_line = i;
    }
    printf("WORDS OF LINE %2d: %2d\n", i, cur_length);
  }
  char longest[STRING_CAPACITY] = {'\0'};
  printf("\nLONGEST LINE [%d]: ", max_line);
  printf("%s\n", roy_string_get_line(longest, str, max_line));
  printf("   ITS LENGTH IS: %2d\n", max_length);

}