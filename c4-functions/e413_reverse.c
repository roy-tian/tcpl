#include <string.h>
#include <stdio.h>

void swap(char * str, int iter1, int iter2) {
  int ch     = str[iter1];
  str[iter1] = str[iter2];
  str[iter2] = ch;
}

void doReverse(char * str, int left, int right) {
  if (left < right) {
    swap(str, left, right);
    doReverse(str, left + 1, right - 1);
  }
}

void reverse(char * str) {
  doReverse(str, 0, strlen(str) - 1);
}

int main(void) {
  char str[] = "My name is Ovuvuevuevue Enyetuenwuevue Ugbemugbem Osas.";
  puts(str);
  reverse(str);
  puts(str);
}