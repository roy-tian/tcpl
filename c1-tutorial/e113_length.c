#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

enum { MAX_LENGTH = 45 };   
static size_t statVec[MAX_LENGTH];

void
stat(const char * str) {
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
histogramH(void) {
  for (int i = 1; i != MAX_LENGTH; i++) {
    size_t currentLength = statVec[i];
    if (currentLength) {
      printf("%2d CHAR: %2d |", i, currentLength);
      for (int i = 0; i != currentLength; i++) {
        printf(" *");
      }
      putchar('\n');
    }
  }
  putchar('\n');
}

void
histogramV(void) {
  size_t nonZeroCount = 0;
  size_t maxLength = 0;

  for (int i = 0; i != MAX_LENGTH; i++) {  
    if (statVec[i] > 0) {
      nonZeroCount++;
    }
    if (statVec[i] > maxLength) {
      maxLength = statVec[i];
    }
  }

  for (size_t i = maxLength; i > 0; i--) {
    for (size_t j = 0; j != MAX_LENGTH; j++) {
      size_t currentLength = statVec[j];
      if (currentLength >= i) {
        printf("*  ");
      } else if (currentLength > 0 && currentLength < i) {
        printf("   ");
      }
    }
    putchar('\n');
  }
  for (int i = 0; i != nonZeroCount * 3; i++) {
    putchar('-');
  }
  putchar('\n');
  for (size_t i = 0; i != MAX_LENGTH; i++) {
    size_t currentLength = statVec[i];
    if (currentLength != 0) {
      printf("%-3zu", i);
    } 
  }
}

int main(void) {
  const char str[] =
    "Telecommunication is the transmission of signs, signals, messages, words, "
    "writings, images and sounds or information of any nature by wire, radio, "
    "optical or other electromagnetic systems.";
    
  stat(str);
  histogramH();
  histogramV();
}