#include <stdio.h>
#include <string.h>

enum {
  STRING_CAPACITY = 1023
};

char *
reverse(char * str) {
  char * pstr_head = str;
  char * pstr_tail = str + strlen(str) - 1;
  while (pstr_tail > pstr_head) {
    char temp = *pstr_head;
    *pstr_head++ = *pstr_tail;
    *pstr_tail-- = temp;
  }
  return str;
}

int main(void) {
  char str[STRING_CAPACITY + 1] = 
    "Twinkle, twinkle, little star, how I wonder what you are.\n"
    "Up above the world so high, like a diamond in the sky.\n"
    "Twinkle, twinkle, little star, how I wonder what you are.";
  
  printf("ORIGINAL STRING\n%s\n", str);
  printf("REVERSED STRING\n%s\n", reverse(str));
  printf("REVERSED TO ORIGINAL\n%s", reverse(str));
}