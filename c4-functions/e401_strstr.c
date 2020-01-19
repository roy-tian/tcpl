#include <stdio.h>
#include <string.h>

// Deprecated: the std version of 'strstr' is magically O(1), 
// so there is no reason to make any alternatives.
int
findSub(const char * str, 
        const char * sub) {
  int iStr = 0;
  int iSub;
  int iCurrent;
  while (*(str + iStr) != '\0') {                  // Traverses all chars in 'str'
    iCurrent = iStr;                               // point to the i-th char of str
    iSub = 0;
    while (*(sub + iSub) != '\0' &&                // if the current char in 'sub' matches 'str'in 'sub'
           *(str + iCurrent) == *(sub + iSub)) {   
      iCurrent++;                                  // go next
      iSub++;                                      // go next
    }
    if (iSub != 0 && *(sub + iSub) == '\0') {      // if matched
      return iStr;                                 // returns the postion
    }
    iStr++;
  }
  return -1;                                       // The loop finished but nothing matched
}

int
findSubR(const char * str,
         const char * sub) {
  int riStr = strlen(str) - strlen(sub);
  int riSub;
  int riCurrent;
  while (riStr >= 0) {
    riCurrent = riStr;
    riSub = strlen(sub) - 1;
    while (riSub >= 0 && *(str + riCurrent) == *(sub + riSub)) {
      riCurrent--;
      riSub--;
    }
    if (riSub == -1) {
      return riStr - strlen(sub) + 1;
    }
    riStr--;
  }
  return -1;
}

int main(void) {
  const char * str = "The bookkeeper keeps the books from being broke.";
  const char * sub = "keep";
  printf(" INDEX: %d\n", findSub(str, sub));
  printf("RINDEX: %d\n", findSubR(str, sub));
}