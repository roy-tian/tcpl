#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum {
  STRING_CAPACITY = 4095
};

char * replaceIndex(char * str, size_t old_sub_pos, size_t old_sub_len, const char * new_sub);
char * replaceBetween(char * str, const char * pattern_head, const char * pattern_tail, const char * new_sub);
char * readFromFile(char * dest, const char * path);
int    appendToFile(const char * src, const char * path);
char * decomment(char * str);

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
replaceBetween(char       * str,
               const char * pattern_head,
               const char * pattern_tail,
               const char * new_sub) {
  char * phead = str;
  bool flag = false;
  while ((phead = strstr(str, pattern_head))) {
    if (flag == true) {
      char * ptail = strstr(phead, pattern_tail);
      replaceIndex(str,
                   phead - str,
                   ptail - phead + strlen(pattern_tail),
                   new_sub);
      flag = false;  
    } else {
      flag = true;
    }
  }
  return str;
}

char * decomment(char * str) {
  replaceBetween(str, "/*", "*/", "");
  replaceBetween(str, "//", "\n", "\n");
  return str;
}

char * readFromFile(char * dest, const char * path) {
  FILE * fp = fopen(path, "r");

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  fread(dest, sizeof(char), size, fp);
  dest[size] = '\0';
  fclose(fp);
  return dest;
}

int appendToFile(const char * src, const char * path) {
  FILE * fp = fopen(path, "a+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}

int main() {
  char str[STRING_CAPACITY + 1] = "\0";
  readFromFile(str, "e123.java");
  decomment(str);
  appendToFile(str, "e123dc.java");
}