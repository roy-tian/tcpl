#include "../include/roystring.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

RoyString roy_string_new(RoyString str, size_t size) {
  return str = calloc(size + 1, sizeof(RoyChar));
}

RoyString roy_string_new_with_content(RoyString str, const RoyString content) {
  str = malloc(strlen(content) + 1);
  memcpy(str, content, strlen(content) + 1);
  return str;
}

void roy_string_delete(RoyString str) {
  free(str);
}

RoyString roy_string_copy(RoyString dest, const RoyString src) {

}

RoyString roy_string_concatenate(RoyString dest, const RoyString src);
RoyString roy_string_to_lower(RoyString str) {
  char * real_str = str;
  while (*str != '\0') {
    *str++ = tolower(*str);
  }
  return real_str;
}

RoyString roy_string_to_upper(RoyString str) {
  char * real_str = str;
  while (*str != '\0') {
    *str++ = toupper(*str);
  }
  return real_str;
}

RoyString roy_string_unique_char(RoyString str, RoyChar ch) {
  RoyString temp_str;
  roy_string_new(temp_str, strlen(str) + 1);
  RoyStringIter ptemp_str = temp_str;
  RoyStringIter real_str = str;
  bool flag = false;
  while (*str != '\0') {
    if (!flag && *str == ch) {
      flag = true;
      *ptemp_str++ = *str++;
    } else if (!flag && *str != ch) {
      *ptemp_str++ = *str++;
    } else if (flag && *str == ch) {
      str++;
    } else { // (flag && *src != ch)
      flag = false;
      *ptemp_str++ = *str++;
    }
  }
  strcpy(real_str, temp_str);
  roy_string_delete(temp_str);
  return real_str;
}

RoyString roy_string_replace_all(RoyString str,
                                 const RoyString old_sub,
                                 const RoyString new_sub) {
  int str_len = strlen(str);
  int old_len = strlen(old_sub);
  int new_len = strlen(new_sub);
  int max_len =
    new_len <= old_len ?
    str_len - str_len / str_len * (old_len - new_len) :
    str_len + str_len / old_len * (new_len - old_len);
  // max_len: possibly max length of the string when its done. 
  ROY_STRING_NEW(temp_str, max_len + 1);

  ROY_STRING_DELETE(temp_str);
}

int roy_string_count_char(const RoyString str, RoyChar ch);
int roy_string_count_char_if(const RoyString str, bool (*condition)(RoyChar));
int roy_string_count_substring(const RoyString str, const RoyString sub);
int roy_string_count_substring_if(const RoyString str, bool (*condition)(RoyString));
int roy_string_count_substring_insensitively(const RoyString str, const RoyString sub);
