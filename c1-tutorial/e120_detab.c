#include <stdio.h>
#include <string.h>

enum {
  STRING_CAPACITY = 1023,
};

char * fillChar(char * dest, int ch, size_t count);
char * replaceIndex(char * str, size_t old_sub_pos, size_t old_sub_len, const char * new_sub);
char * detab(char * str, size_t tab_size);

char *
fillChar(char * dest,
         int    ch,
         size_t count) {
  size_t i = 0;
  for (; i != count; i++) {
    *(dest + i) = ch;
  }
  *(dest + i) = '\0';
  return dest;
}

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

char * detab(char * str, size_t tab_size) {
  char * pstr = str;
  size_t tab_marker = 0;
  while (*pstr != '\0') {
    if (*pstr == '\t') {
      char rpt_str[STRING_CAPACITY + 1] = "\0";
      size_t rpt_count = tab_size - tab_marker % tab_size;
      fillChar(rpt_str, ' ', rpt_count);
      replaceIndex(str, pstr - str, 1, rpt_str);
      tab_marker += rpt_count - 1;
      pstr += rpt_count - 1;
    } else if (*pstr == '\n') {
      tab_marker = 0;
      pstr++;
    } else {
      tab_marker++;
      pstr++;
    }
  }
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] = 
    "Fly,\tfly,\tfly\tyour\tkite,\n"
    "High  \t  in   \tthe\t sky;\t\n"
    "\t  \t \t\n"
    "\tUp and \t\t down,\n"
    "   \tRound and round,\n"
    "Let \tyour\t kite fly high.";
  FILE * fp = fopen("e120.txt", "w+");
  fputs("ORIGINAL STRING\n=============\n", fp);
  fputs(str, fp);
  fputs("\n\nDETABED STRING\n============\n", fp);
  fputs(detab(str, 8), fp);
  fclose(fp);
}
