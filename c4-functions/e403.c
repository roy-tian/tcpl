#include <stdio.h>

#define STRING_CAPACITY 1023

typedef struct Song_ {
  char title[STRING_CAPACITY + 1];
  char artist[STRING_CAPACITY + 1];
  int year;
  int volume;
  char genre[STRING_CAPACITY + 1]; 
} Song;

int main(void) {
  Song *s1 = malloc(sizeof(Song));
  
}