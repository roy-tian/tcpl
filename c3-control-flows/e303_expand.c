#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { BUFFER_SIZE = 128 };

/* Makes a sequence from 'front' to 'back'.
   e.g. front=a, back=g, sequence=abcefg */
char *
sequence(char * dest,
         int    front,
         int    back) {
  char * pdest = dest;
  while (front <= back) {
    *pdest++ = front++;
  }
  *pdest = '\0';
  return dest;
}

char *
fillSequence(char       * dest,
             const char * pattern) {
  enum Flag { LEFT, MIDDLE, RIGHT };
  enum Flag flag = 0;
  char * pDest = dest;
  while (*pattern != '\0') {
    if (flag == LEFT && isprint(*pattern)) {
      flag = MIDDLE;
    } else if (flag == MIDDLE && *pattern == '-') {
      flag = RIGHT;
    } else if (flag == RIGHT && isprint(*pattern)) {
      char buf[BUFFER_SIZE] = "\0";
      strcat(dest, sequence(buf, *(pattern - 2), *pattern));
      pDest += strlen(buf);
      flag = LEFT;
    } else if (flag == MIDDLE && isprint(*pattern)) {
      *pDest++ = *(pattern - 1);
    }
    pattern++;
  }
  while (flag > 0) {
    *pDest++ = *(pattern - flag--);
  }
  *pDest = '\0';
  return dest;
}

/* An algorithm far more effective than mine, invented by Axel-Tobias Schreiner, 
   when he was a CS Professor at University of Osnabrück.
   I think 'a--' is an incorrect input and should return a nil string,
   but this function returns 'a--' itself, which, to my opinion, is negotiable. */
char *
fillSequenceAS(char       * dest,
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
  char buf[BUFFER_SIZE] = "\0";
  puts(fillSequence  (buf, "-a----z0-9-"));
  puts(fillSequenceAS(buf, "-a----z0-9-"));
}