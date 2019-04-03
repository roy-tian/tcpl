#include "roystring.h"
#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 45

int lengths[MAX_LENGTH] = {0};

void stat(const char * str) {
  const char * pstr = str;
  bool flag = false;
  int cur_len = 0;
  do {
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
  } while (*pstr != '\0');
}

int main(void) {
  char str[STRING_CAPACITY] =
    "Telecommunication is the transmission of signs, signals, messages, words, "
    "writings, images and sounds or information of any nature by wire, radio, "
    "optical or other electromagnetic systems.";
  for (int i = 1; i != MAX_LENGTH; i++) {
    int cur_count = roy_string_count_word_if(str, i);
    if (cur_count) {
      printf("%2d-CHARACTER WORD: %2d\n", i, cur_count);
    }
  }
  printf("TOTAL WORD: %2zu\n", roy_string_count_word(str));
}