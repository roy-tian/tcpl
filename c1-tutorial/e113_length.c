#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 1023,
  MAX_LENGTH = 45
};

size_t statVec[MAX_LENGTH] = {0};

void
lengthStats(const char * str) {
  bool flag = false;
  size_t currentLength = 0;
  do {
    if (!flag && isalnum(*str)) {
      currentLength++;
      flag = true;
    } else if (flag && isalnum(*str)) {
      currentLength++;
    } else if (flag && !isalnum(*str)) {
      statVec[currentLength]++;
      currentLength = 0;
      flag = false;
    } // (!flag && !isalnum(*pstr)) does nothing
    str++;
  } while (*str != '\0');
}

void
histogramHorizontal(void) {
  for (int i = 1; i != MAX_LENGTH; i++) {
    size_t currentCount = statVec[i];
    if (currentCount) {
      printf("%2d CHAR: %2d |", i, currentCount);
      for (int i = 0; i != currentCount; i++) {
        printf(" *");
      }
      printf("\n");
    }
  }
  printf("\n");
}

void
histogramVertical(void) {
  size_t nonZeroLength = 0;
  size_t maxCount = 0;

  for (int i = 0; i != MAX_LENGTH; i++) {  
    if (statVec[i] > 0) {
      nonZeroLength++;
    }
    if (statVec[i] > maxCount) {
      maxCount = statVec[i];
    }
  }

  for (size_t i = maxCount; i > 0; i--) {
    for (size_t j = 0; j != MAX_LENGTH; j++) {
      size_t currentCount = statVec[j];
      if (currentCount >= i) {
        printf("*  ");
      } else if (currentCount > 0 && currentCount < i) {
        printf("   ");
      }
    }
    printf("\n");
  }
  for (int i = 0; i != nonZeroLength * 3; i++) {
    printf("-");
  }
  printf("\n");
  for (size_t i = 0; i != MAX_LENGTH; i++) {
    size_t currentCount = statVec[i];
    if (currentCount != 0) {
      printf("%-3zu", i);
    } 
  }
}

int main(void) {
  const char str[STRING_CAPACITY + 1] =
    "Telecommunication is the transmission of signs, signals, messages, words, "
    "writings, images and sounds or information of any nature by wire, radio, "
    "optical or other electromagnetic systems.";
    
  lengthStats(str);
  histogramHorizontal();
  histogramVertical();
}