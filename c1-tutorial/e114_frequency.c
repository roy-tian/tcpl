/**
 * This file should be saved with encoding 'gbk'
 * and run on cmd of Windows,
 * in order to print histogram correctly.
 */

#include <stdio.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 1023,
  N_MAX = 26
};

size_t stats_v[N_MAX] = {0};

void
charStats(const char * str) {
  while (*str != '\0') {
    if (isupper(*str)) {
      stats_v[*str - 'A']++;
    } else if (islower(*str)) {
      stats_v[*str - 'a']++;
    }
    str++;
  }
}

void
histogram(void) {
  const char blocks[STRING_CAPACITY + 1] = "¨x¨y¨z¨{¨|¨}¨~¨€";
  size_t non_zero_length = 0;
  size_t max_count = 0;

  for (int i = 0; i != N_MAX; i++) {  
    if (stats_v[i] > 0) {
      non_zero_length++;
    }
    if (stats_v[i] > max_count) {
      max_count = stats_v[i];
    }
  }

  for (size_t i = max_count / 8 + 1; i > 0; i--) {
    for (size_t j = 0; j != N_MAX; j++) {
      size_t cur_count = stats_v[j];
      if (cur_count > 0) {
        if (cur_count / 8 + 1 > i ||
            cur_count / 8 + 1 == i && cur_count % 8 == 0) {
          putchar(blocks[14]);
          putchar(blocks[15]);
          putchar(' ');
        } else if (cur_count / 8 + 1 == i && cur_count % 8 != 0) {
          putchar(blocks[cur_count % 8 * 2 - 2]);
          putchar(blocks[cur_count % 8 * 2 - 1]);
          putchar(' ');
        } else {
          putchar(' ');
          putchar(' ');
          putchar(' ');
        }
      }
    }
    puts("");
  }
  for (int i = 0; i != non_zero_length * 3; i++) {
    putchar('-');
  }
  puts("");
  for (int i = 0; i != N_MAX; i++) {
    size_t cur_count = stats_v[i];
    if (cur_count != 0) {
      putchar('A' + i);
      putchar(' ');
      putchar(' ');
    } 
  }
}

int main(void) {
  char str[STRING_CAPACITY + 1] =
    "In the year 2633, the evil Red Falcon Organization have set a base on the "
    "Galuga archipelago near New Zealand in a plot to conquer the world. "
    "Two commandos, Bill Rizer and Lance Bean of the Contra unit "
    "(an elite group of soldiers specializing in guerrilla warfare), "
    "are sent to the island to destroy the enemy forces and "
    "uncover the true nature of Red Falcon, the alien entity controlling them.";

  charStats(str);
  histogram();
}