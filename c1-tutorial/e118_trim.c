#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_CAPACITY 1023

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

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
  size_t count = roy_string_count_char(str, '\n');
  size_t str_length = strlen(str);
  if (str_length != 0 && *(str + str_length - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
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

char * roy_string_trim_line(char * str) {
  char * pstr_tail = str + strlen(str);
  while (str < pstr_tail && isblank(*(pstr_tail - 1))) {
    pstr_tail--;
  }
  *pstr_tail = '\0';
  return str;
}

char * roy_string_trim(char * str) {
  size_t capacity = strlen(str);
  ROY_STRING(temp_str, capacity);
  for (int i = 1; i <= roy_string_count_line(str); i++) {
    ROY_STRING(cur_line, capacity);
    roy_string_line(cur_line, str, i);
    roy_string_trim_line(cur_line);
    if (strlen(cur_line) != 0) { 
      strcat(temp_str, "\n");
      strcat(temp_str, cur_line);
    }
  }
  strcpy(str, temp_str + 1);
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] =
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
    fputs(roy_string_trim(str), fp);
    fclose(fp);
}