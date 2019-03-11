#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LENGTH 45
#define STRING_CAPACITY 1024

int lengths[MAX_LENGTH] = {0};

void stat(const char * str) {
  const char * pstr = str;
  bool flag = false;
  int cur_len = 0;
  while (*pstr != '\0') {
    if (!flag && isalnum(*pstr)) {
      flag = true;
      cur_len ++;
    } else if (flag && isalnum(*pstr)) {
      cur_len ++;
    } else if (flag && !isalnum(*pstr)) {
      flag = false;
      lengths[cur_len]++;
      cur_len = 0;
    } // (!flag && !iscntrl(*pstr)) does nothing
    pstr++;
  }
}

int count_strlen(const char * str, int len) {
  const char * pstr = str;
  bool flag = false;
  int cur_len = 0;
  int count = 0;
  while (*pstr != '\0') {
    if (!flag && isalnum(*pstr)) {
      flag = true;
      cur_len ++;
    } else if (flag && isalnum(*pstr)) {
      cur_len ++;
    } else if (flag && !isalnum(*pstr)) {
      flag = false;
      if (cur_len == len) {
        count++;
      }
      cur_len = 0;
    } // (!flag && !iscntrl(*pstr)) does nothing
    pstr++;
  }
  return count;
}

int main(void) {
  char str[STRING_CAPACITY] =
    "Telecommunication is the transmission of signs, signals, messages, words, "
    "writings, images and sounds or information of any nature by wire, radio, "
    "optical or other electromagnetic systems.";
  for (int i = 1; i != MAX_LENGTH; i++) {
    int cur_count = count_strlen(str, i);
    if (cur_count) {
      printf("%2d-CHARACTER WORD: %2d\n", i, cur_count);
    }
  }
}