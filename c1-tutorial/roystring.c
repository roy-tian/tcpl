#include "roystring.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char * roy_string_to_lower(char * str) {
  char * real_str = str;
  while ((*str++ = tolower(*str)) != '\0') {
    ;
  }
  return real_str;
}

char * roy_string_to_upper(char * str) {
  char * real_str = str;
  while ((*str++ = toupper(*str)) != '\0') {
    ;
  }
  return real_str;
}

char * roy_string_unique_char(char * str, int ch) {
  // a temporary-stored string.
  char * temp_str = calloc(strlen(str), sizeof(char));
  // a pointer to the real temp_str.
  char * ptemp_str = temp_str;
  // a pointer to the real str.
  char * real_str = str;
  // stand when the first 'ch' is tracked, lay down when repeating 'ch's end.
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
  free(temp_str);
  return real_str;
}

// Replaces all 'old_sub' acurred with 'new_sub'.
// The behavior is undefined when the length of str grows out of its size,
// risen when new_sub is larger than old_sub.
char * roy_string_replace_all(char * str,
                              const char * old_sub,
                              const char * new_sub) {
  // the length should be when all work 
  int len_after = strlen(str);
  len_after += roy_string_count_substring(str, old_sub, true) *
               (strlen(new_sub) - strlen(old_sub));
  // a temporary-stored string.
  char * temp_str = calloc(len_after, sizeof(char));
  // a pointer to the real temp_str.
  char * ptemp_str = temp_str;
  // a pointer to the real str.
  char * real_str = str;
  // a pointer to the beginning of a matched substring.
  char * match_begin;
  while (match_begin = strstr(str, old_sub)) {
    strncat(ptemp_str, str, match_begin - str);
    strcat(ptemp_str, new_sub);
    str = match_begin + strlen(old_sub);
  }
  strcat(temp_str, str);
  strcpy(real_str, temp_str);
  free(temp_str);
  return real_str;
}

int roy_string_count_char(const char * str, int ch) {
  int count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

int roy_string_count_char_if(const char * str, int (*condition)(int)) {
  int count = 0;
  while (*str != '\0') {
    if (condition(*str++)) {
      count ++;
    }
  }
  return count;
}

int roy_string_count_substring(const char * str,
                               const char * sub,
                               bool sensibility) {
  int count = 0;
  const char * pstr;
  const char * psub;
  char * lower_str;
  char * lower_sub;

  if (sensibility) {
    pstr = str;
    psub = sub;
  } else {
    lower_str = calloc(strlen(str) + 1, sizeof(char));
    strcpy(lower_str, str);
    roy_string_to_lower(lower_str);
    pstr = lower_str;

    lower_sub = calloc(strlen(sub) + 1, sizeof(char));
    strcpy(lower_sub, sub);
    roy_string_to_lower(lower_sub);
    psub = lower_sub;
  }

  char * match_begin;
  while (match_begin = strstr(pstr, psub)) {
    count++;
    pstr = match_begin + strlen(psub);
  } 
  if (!sensibility) {
    free(lower_sub);
    free(lower_str);
  }
  return count;
}
// Counts the number of words in 'str'.
int roy_string_count_word(const char * str) {
  const char * pstr = str;
  int count = 0;
  bool flag = false;
  while (*pstr != '\0') {

  }
}

// Counts how many words in 'str' is 'length'-character long.
// counts total number of words if 'length' is 0.
int roy_string_count_word_length(const char * str, int length) {
  const char * pstr = str;
  bool flag = false;
  int length_cur = 0;
  int count_cur = 0;
  int count_sum = 0;
  while (*pstr != '\0') {
    if (!flag && isalnum(*pstr)) {
      flag = true;
      length_cur ++;
    } else if (flag && isalnum(*pstr)) {
      length_cur ++;
    } else if (flag && !isalnum(*pstr)) {
      flag = false;
      if (length_cur == length) {
        count_cur++;
      }
      length_cur = 0;
      count_sum++;
    } // (!flag && !isalnum(*pstr)) does nothing
    pstr++;
  }
  if (length_cur != 0) {
      if (length_cur == length) {
        count_cur++;
      }
      count_sum++;
  }
  return length == 0 ? count_sum : count_cur ;
}