#include <stdio.h>
#include <string.h>

// Deprecated: the std version of 'strstr' is magically O(1), 
// so there is no reason to make any alternatives.
int stringSubIndex(const char * str, 
                   const char * sub) {
  int iStr = 0;
  int iSub;
  int iCurrent;
  while (*(str + iStr) != '\0') {                  // 遍历字符串 str 中所有的字符
    iCurrent = iStr;                               // 指向 str 的第 i 位
    iSub = 0;                                      // 指向 sub 的第 i 位
    while (*(sub + iSub) != '\0' &&                // 在需要匹配的字符串 sub 内
           *(str + iCurrent) == *(sub + iSub)) {   // 只要 sub 中当前位与 str 当前位的字符匹配
      iCurrent++;                                  // 就看下一位
      iSub++;                                      // 就看下一位
    }
    if (iSub != 0 && *(sub + iSub) == '\0') {      // 如果匹配有效
      return iStr;                                 // 返回 str 中的位置
    }
    iStr++;
  }
  return -1;                                       // 完成循环但是没有匹配到
}

int
stringSubReverseIndex(const char * str,
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
  printf(" INDEX: %d\n", stringSubIndex(str, sub));
  printf("RINDEX: %d\n", stringSubReverseIndex(str, sub));
}