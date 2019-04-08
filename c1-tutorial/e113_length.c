#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define STRING_CAPACITY 1023
#define WORD_LENGTH_MAX 45

void roy_string_word_length_stats(const char * str,  size_t * stats_v);
void histogram_horizontal(const size_t * stats_v);
void histogram_vertical(const size_t * stats_v);

void roy_string_word_length_stats(const char * str,  size_t * stats_v) {
  bool flag = false;
  size_t cur_length = 0;
  do {
    if (!flag && isalnum(*str)) {
      cur_length++;
      flag = true;
    } else if (flag && isalnum(*str)) {
      cur_length++;
    } else if (flag && !isalnum(*str)) {
      stats_v[cur_length]++;
      cur_length = 0;
      flag = false;
    } // (!flag && !isalnum(*pstr)) does nothing
    str++;
  } while (*str != '\0');
}

void histogram_horizontal(const size_t * stats_v) {
  for (int i = 1; i != WORD_LENGTH_MAX; i++) {
    size_t cur_count = stats_v[i];
    if (cur_count) {
      printf("%2d CHAR: %2d |", i, cur_count);
      for (int i = 0; i != cur_count; i++) {
        printf(" *");
      }
      printf("\n");
    }
  }
  printf("\n");
}

void histogram_vertical(const size_t * stats_v) {
  size_t non_zero_length = 0;
  size_t max_count = 0;

  for (int i = 0; i != WORD_LENGTH_MAX; i++) {  
    if (stats_v[i] > 0) {
      non_zero_length++;
    }
    if (stats_v[i] > max_count) {
      max_count = stats_v[i];
    }
  }

  for (size_t i = max_count; i > 0; i--) {
    for (size_t j = 0; j != WORD_LENGTH_MAX; j++) {
      size_t cur_count = stats_v[j];
      if (cur_count >= i) {
        printf("*  ");
      } else if (cur_count > 0 && cur_count < i) {
        printf("   ");
      }
    }
    printf("\n");
  }
  for (int i = 0; i != non_zero_length * 3; i++) {
    printf("-");
  }
  printf("\n");
  for (size_t i = 0; i != WORD_LENGTH_MAX; i++) {
    size_t cur_count = stats_v[i];
    if (cur_count != 0) {
      printf("%-3zu", i);
    } 
  }
}

int main(void) {
  const char str[STRING_CAPACITY + 1] =
    "Telecommunication is the transmission of signs, signals, messages, words, "
    "writings, images and sounds or information of any nature by wire, radio, "
    "optical or other electromagnetic systems.";

  size_t stats_v[WORD_LENGTH_MAX] = {0};
  size_t non_zero_length = 0;
  size_t max_count = 0;

  roy_string_word_length_stats(str, stats_v);
  histogram_horizontal(stats_v);
  histogram_vertical(stats_v);
}