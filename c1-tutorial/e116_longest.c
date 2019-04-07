#include <stdio.h>
#include <string.h>
#define STRING_CAPACITY 1023


size_t roy_string_count_char(const char * str, int ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t roy_string_count_line(const char * str) {
  size_t str_length = strlen(str);
  size_t count = roy_string_count_char(str, '\n');
  if (str_length != 0 && *(str + str_length - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

size_t roy_string_line_length(const char * str, size_t line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * str_tail = strchr(str, '\n');
  if (!str_tail) {
    return strlen(str);
  } else {
    return str_tail - str;
  }
}

char * roy_string_line(char * line_content,
                       const char * str,
                       size_t line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * str_tail = strchr(str, '\n');
  if (!str_tail) {
    strcpy(line_content, str);
  } else {
    strncpy(line_content, str, str_tail - str);
  }
  return line_content;
}

int main(void) {
  const char str[STRING_CAPACITY + 1] =
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
  printf("%s\n", roy_string_line(longest, str, max_line));
  printf("   ITS LENGTH IS: %2d\n", max_length);

}