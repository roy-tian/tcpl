#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 127
};

// Makes a sequence from 'front_ch' to 'back'
char * sequence(char * dest, int front_ch, int back_ch);
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
         int    front_ch,
         int    back_ch) {
  char * pdest = dest;
  while (front_ch <= back_ch) {
    *pdest++ = front_ch++;
  }
  *pdest = '\0';
  return dest;
}

char *
fillSequence(char       * dest,
             const char * pattern) {
  int flag = 0;
  char * pdest = dest;
  while (*pattern != '\0') {
    if (flag == 0 && isprint(*pattern)) {
      flag++;
    } else if (flag == 1 && *pattern == '-') {
      flag++;
    } else if (flag == 2 && isprint(*pattern)) {
      char buf[STRING_CAPACITY + 1] = "\0";
      strcat(dest, sequence(buf, *(pattern - 2), *pattern));
      pdest += strlen(buf);
      flag = 0;
    } else if (flag == 1 && isprint(*pattern)) {
      *pdest++ = *(pattern - 1);
      flag = 1;
    }
    pattern++;
  }
  while (flag > 0) {
    *pdest++ = *(pattern - flag--);
  }
  *pdest = '\0';
  return dest;
}


char *
asFillSequence(char       * dest,
               const char * pattern) {
  int i_pattern = 0, i_dest = 0;
  int ch;
  while ((ch = pattern[i_pattern++]) != '\0') {
    if (pattern[i_pattern] == '-' && pattern[i_pattern + 1] >= ch) {
      i_pattern++;
      while (ch < pattern[i_pattern]) {
        dest[i_dest++] = ch++;
      }
    } else {
      dest[i_dest++] = ch;
    }
  }
  dest[i_dest] = '\0';
  return dest;
}

int main(void) {
  char buf[STRING_CAPACITY + 1] = "\0";
  puts(fillSequence(buf, "-a----z0-9-"));
  puts(asFillSequence(buf, "-a----z0-9-"));
}