#include <stdio.h>
#include <string.h>

#define STRING_CAPACITY 1023
#define TAB_SIZE 4
#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_replace_index(char * str,
                                size_t old_sub_pos,
                                size_t old_sub_len,
                                const char * new_sub);
char * roy_string_entab(char * str, size_t tab_size);                             

char * roy_string_replace_index(char * str,
                                size_t old_sub_pos,
                                size_t old_sub_len,
                                const char * new_sub) {
  ROY_STRING(temp_str, strlen(str) + strlen(new_sub) - old_sub_len)
  strncpy(temp_str, str, old_sub_pos);
  strcat(temp_str, new_sub);
  strcat(temp_str, str + old_sub_pos + old_sub_len);
  strcpy(str, temp_str);
  return str;
}

char * roy_string_entab(char * str, size_t tab_size) {
  char * pstr = str;
  size_t pos = 1;
  while (*pstr != '\0') {
    if (*pstr == ' ' && pos % tab_size == 0) {
      char * pblank = pstr;
      while (*pblank == ' ') {
        pblank--;
      }
      roy_string_replace_index(str, pblank - str + 1, pstr - pblank, "\t");
      pos += pstr - pblank - 1;
    }
    if (*pstr == '\n') {
      pos = 0;
    }
    pstr++;
    pos++;
  }
  return str;
}

int main(void) {
  char str[STRING_CAPACITY] =
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
  FILE * fp = fopen("e121.txt", "w+");
  fputs("ORIGINAL CODE:\n=============\n", fp);
  fputs(str, fp);
  fputs("\n\nAFTER ENTAB:\n=============\n", fp);
  fputs(roy_string_entab(str, TAB_SIZE), fp);
  fclose(fp);
}
