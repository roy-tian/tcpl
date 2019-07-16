#include <stdio.h>
#include <string.h>

enum {
  STRING_CAPACITY = 1023
};

char * replaceIndex(char * str, size_t old_sub_pos, size_t old_sub_len, const char * new_sub);
char * entab(char * str, size_t tab_size);

char *
replaceIndex(char       * str,
             size_t       old_sub_pos,
             size_t       old_sub_len,
             const char * new_sub) {
  char temp_str[STRING_CAPACITY + 1] = "\0";
  strncpy(temp_str, str, old_sub_pos);
  strcat(temp_str, new_sub);
  strcat(temp_str, str + old_sub_pos + old_sub_len);
  strcpy(str, temp_str);
  return str;
}

char *
entab(char   * str,
      size_t   tab_size) {
  char * pstr = str;
  size_t pos = 1;
  while (*pstr != '\0') {
    if (*pstr == ' ' && pos % tab_size == 0) {
      char * pblank = pstr;
      while (*pblank == ' ') {
        pblank--;
      }
      replaceIndex(str, pblank - str + 1, pstr - pblank, "\t");
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
  char str[STRING_CAPACITY + 1] =
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
  fputs(entab(str, 4), fp);
  fclose(fp);
}
