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

size_t statVec[N_MAX] = {0};

void
charStats(const char * str) {
  while (*str != '\0') {
    if (isupper(*str)) {
      statVec[*str - 'A']++;
    } else if (islower(*str)) {
      statVec[*str - 'a']++;
    }
    str++;
  }
}

void
histogram(void) {
  const char blocks[STRING_CAPACITY + 1] = "¨x¨y¨z¨{¨|¨}¨~¨€";
  size_t nonZeroLength = 0;
  size_t maxCount = 0;

  for (int i = 0; i != N_MAX; i++) {  
    if (statVec[i] > 0) {
      nonZeroLength++;
    }
    if (statVec[i] > maxCount) {
      maxCount = statVec[i];
    }
  }

  for (size_t i = maxCount / 8 + 1; i > 0; i--) {
    for (size_t j = 0; j != N_MAX; j++) {
      size_t currentCount = statVec[j];
      if (currentCount > 0) {
        if (currentCount / 8 + 1 > i ||
            currentCount / 8 + 1 == i && currentCount % 8 == 0) {
          putchar(blocks[14]);
          putchar(blocks[15]);
          putchar(' ');
        } else if (currentCount / 8 + 1 == i && currentCount % 8 != 0) {
          putchar(blocks[currentCount % 8 * 2 - 2]);
          putchar(blocks[currentCount % 8 * 2 - 1]);
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
  for (int i = 0; i != nonZeroLength * 3; i++) {
    putchar('-');
  }
  puts("");
  for (int i = 0; i != N_MAX; i++) {
    size_t currentCount = statVec[i];
    if (currentCount != 0) {
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