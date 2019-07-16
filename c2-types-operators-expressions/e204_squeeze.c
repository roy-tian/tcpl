#include <stdio.h>
#include <string.h>

enum {
  STRING_CAPACITY = 1023
};

char * squeeze(char * str, const char * set) {
  int i = 0, j = 0;
  while (*(str + i) != '\0') {
    if (strchr(set, *(str + i))) { /* character belongs to 'set' */
      i++;                         /* will be squeezed. */
    } else {
      *(str + j++) = *(str + i++);
    }
  }
  *(str + j) = '\0';
  return str;
}

int main(void) {
  char str[STRING_CAPACITY] = 
    "THIS IS THE NEW SHIT\n"
    "Everything has been said before,\n"
    "There's nothing left to say anymore;\n"
    "When it's all the same, you can ask for it by name.\n"
    "Babble, babble, bitch, bitch\n"
    "Rebel, rebel, party, party\n"
    "Sex, sex, sex and don't forget the violence\n"
    "Blah, blah, blah, got your lovey-dovey, sad-and-lonely\n"
    "Stick your stupid slogan in\n"
    "Everybody sing along.\n"
    "Are you motherfuckers ready for the new shit?\n"
    "Stand up and admit tomorrow's never coming\n"
    "This is the new shit\n"
    "Stand up and admit\n"
    "Do we get it? \"No!\"\n"
    "Do we want it? \"Yeah!\"\n"
    "This is the new shit\n"
    "Stand up and admit.\n";
  printf("ORIGNAL LYRIC:\n==============\n");
  printf("%s", str);

  printf("\nLYRIC WITHOUT PUNCUATION:\n========================\n");
  printf("%s", squeeze(str, "\"'.,?!;"));
}