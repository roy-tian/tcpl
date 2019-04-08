#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRING_CAPACITY 1023
#define STRING_CAPACITY_HUGE 65535
#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_replace_index(char * str,
                                size_t old_sub_pos,
                                size_t old_sub_len,
                                const char * new_sub);
char * replace_between(char * str,
                       const char * pattern_head,
                       const char * pattern_tail,
                       const char * new_sub);
char * decomment(char * str);
char * roy_string_read_from_file(char * dest, const char * path);
int roy_string_append_to_file(const char * src, const char * path);


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

char * replace_between(char * str,
                       const char * pattern_head,
                       const char * pattern_tail,
                       const char * new_sub) {
  char * phead = str;
  bool flag = false;
  while ((phead = strstr(str, pattern_head))) {
    if (flag == true) {
      char * ptail = strstr(phead, pattern_tail);
      roy_string_replace_index(str,
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
  replace_between(str, "/*", "*/", "");
  replace_between(str, "//", "\n", "\n");
  return str;
}

char * roy_string_read_from_file(char * dest, const char * path) {
  FILE * fp = fopen(path, "r");
  ROY_STRING(buf, STRING_CAPACITY)
  fgets(buf, STRING_CAPACITY, fp);
  strcpy(dest, buf);
  while (fgets(buf, STRING_CAPACITY, fp)) {
    strcat(dest, buf);
  }
  fclose(fp);
  return dest;
}

int roy_string_append_to_file(const char * src, const char * path) {
  FILE * fp = fopen(path, "a+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}

int main() {
  ROY_STRING(str, STRING_CAPACITY_HUGE)
  roy_string_read_from_file(str, "e123.java");
  decomment(str);
  roy_string_append_to_file(str, "e123dc.java");
}