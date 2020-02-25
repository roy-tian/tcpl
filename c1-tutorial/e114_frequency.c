/* This file should be saved with encoding 'gbk' and run on cmd of Windows,
   or the histogram won't show up correctly. */

#include <stdio.h>
#include <ctype.h>

enum {
  BUFFER_SIZE = 1024,
  MAX_CHAR = 26
};

static size_t statVec[MAX_CHAR];

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
  const char blocks[] = "�x�y�z�{�|�}�~��";
  size_t nonZeroLength = 0;
  size_t maxLength = 0;

  for (int i = 0; i != MAX_CHAR; i++) {  
    if (statVec[i] > 0) {
      nonZeroLength++;
    }
    if (statVec[i] > maxLength) {
      maxLength = statVec[i];
    }
  }

  for (size_t i = maxLength / 8 + 1; i > 0; i--) {
    for (size_t j = 0; j != MAX_CHAR; j++) {
      size_t currentLength = statVec[j];
      if (currentLength > 0) {
        if (currentLength / 8 + 1 > i ||
            currentLength / 8 + 1 == i && currentLength % 8 == 0) {
          putchar(blocks[14]);
          putchar(blocks[15]);
          putchar(' ');
        } else if (currentLength / 8 + 1 == i && currentLength % 8 != 0) {
          putchar(blocks[currentLength % 8 * 2 - 2]);
          putchar(blocks[currentLength % 8 * 2 - 1]);
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
  for (int i = 0; i != MAX_CHAR; i++) {
    size_t currentCount = statVec[i];
    if (currentCount != 0) {
      putchar('A' + i);
      putchar(' ');
      putchar(' ');
    } 
  }
}

int main(void) {
  char str[BUFFER_SIZE] =
    "In the year 2633, the evil Red Falcon Organization have set a base on the "
    "Galuga archipelago near New Zealand in a plot to conquer the world. "
    "Two commandos, Bill Rizer and Lance Bean of the Contra unit "
    "(an elite group of soldiers specializing in guerrilla warfare), "
    "are sent to the island to destroy the enemy forces and "
    "uncover the true nature of Red Falcon, the alien entity controlling them.";

  charStats(str);
  histogram();
}