#include <stdio.h>
#include <string.h>

char *
reverse(char * str) {
  char * pStrHead = str;
  char * pStrTail = str + strlen(str) - 1;
  while (pStrTail > pStrHead) {
    char temp = *pStrHead;
    *pStrHead++ = *pStrTail;
    *pStrTail-- = temp;
  }
  return str;
}

int main(void) {
  char str[] = 
    "Twinkle, twinkle, little star, how I wonder what you are.\n"
    "Up above the world so high, like a diamond in the sky.\n"
    "Twinkle, twinkle, little star, how I wonder what you are.";
  
  puts("ORIGINAL STRING");
  puts(str);
  puts("\nREVERSED STRING");
  puts(reverse(str));
  puts("\nREVERSED TO ORIGINAL");
  puts(reverse(str));
}