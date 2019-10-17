#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 127
};

// Makes a sequence from 'front_ch' to 'back'
char * sequence(char * dest, int frontCh, int backCh);
char * fillSequence(char * dest, const char * pattern);
// An algorithm far more effective than mine,
// invented by Axel-Tobias Schreiner, 
// when he was a CS Professor at University of Osnabrück.
// I think 'a--' is an incorrect input and should return a nil string,
// but this function will return 'a--' itself, 
// which, to my opinion, is a behavior not unified.
char * asFillSequence(char * dest, const char * pattern);

char *
sequence(char * dest,
         int    frontCh,
         int    backCh) {
  char * pdest = dest;
  while (frontCh <= backCh) {
    *pdest++ = frontCh++;
  }
  *pdest = '\0';
  return dest;
}

char *
fillSequence(char       * dest,
             const char * pattern) {
  int flag = 0;
  char * pDest = dest;
  while (*pattern != '\0') {
    if (flag == 0 && isprint(*pattern)) {
      flag++;
    } else if (flag == 1 && *pattern == '-') {
      flag++;
    } else if (flag == 2 && isprint(*pattern)) {
      char buf[STRING_CAPACITY + 1] = "\0";
      strcat(dest, sequence(buf, *(pattern - 2), *pattern));
      pDest += strlen(buf);
      flag = 0;
    } else if (flag == 1 && isprint(*pattern)) {
      *pDest++ = *(pattern - 1);
      flag = 1;
    }
    pattern++;
  }
  while (flag > 0) {
    *pDest++ = *(pattern - flag--);
  }
  *pDest = '\0';
  return dest;
}


char *
asFillSequence(char       * dest,
               const char * pattern) {
  int iPattern = 0;
  int iDest = 0;
  int ch;
  while ((ch = pattern[iPattern++]) != '\0') {
    if (pattern[iPattern] == '-' && pattern[iPattern + 1] >= ch) {
      iPattern++;
      while (ch < pattern[iPattern]) {
        dest[iDest++] = ch++;
      }
    } else {
      dest[iDest++] = ch;
    }
  }
  dest[iDest] = '\0';
  return dest;
}

int main(void) {
  char buf[STRING_CAPACITY + 1] = "\0";
  puts(fillSequence(buf, "-a----z0-9-"));
  puts(asFillSequence(buf, "-a----z0-9-"));
}