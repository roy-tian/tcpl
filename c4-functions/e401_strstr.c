#include <stdio.h>
#include <string.h>

// Deprecated: the std version of 'strstr' is magically O(1), 
// so there is no reason to make any alternatives.
int stringSubIndex(const char * str, 
                   const char * sub) {
  int i_str = 0, i_str_cur, i_sub;
  while (*(str + i_str) != '\0') {                 // 遍历字符串 str 中所有的字符
    i_str_cur = i_str;                             // 指向 str 的第 i 位
    i_sub = 0;                                     // 指向 sub 的第 i 位
    while (*(sub + i_sub) != '\0' &&               // 在需要匹配的字符串 sub 内
           *(str + i_str_cur) == *(sub + i_sub)) { // 只要 sub 中当前位与 str 当前位的字符匹配
      i_str_cur++;                                 // 就看下一位
      i_sub++;                                     // 就看下一位
    }
    if (i_sub != 0 && *(sub + i_sub) == '\0') {    // 如果匹配有效
      return i_str;                                // 返回 str 中的位置
    }
    i_str++;
  }
  return -1;                                       // 完成循环但是没有匹配到
}

int
stringSubReverseIndex(const char * str,
                      const char * sub) {
  int ri_str = strlen(str) - strlen(sub);
  int ri_str_cur, ri_sub;
  while (ri_str >= 0) {
    ri_str_cur = ri_str;
    ri_sub = strlen(sub) - 1;
    while (ri_sub >= 0 && *(str + ri_str_cur) == *(sub + ri_sub)) {
      ri_str_cur--;
      ri_sub--;
    }
    if (ri_sub == -1) {
      return ri_str - strlen(sub) + 1;
    }
    ri_str--;
  }
  return -1;
}

int main(void) {
  const char * str = "The bookkeeper keeps the books from being broke.";
  const char * sub = "keep";
  printf(" INDEX: %d\n", stringSubIndex(str, sub));
  printf("RINDEX: %d\n", stringSubReverseIndex(str, sub));
}