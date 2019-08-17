#include "sort.h"
#include "roy.h"

int compPage(const char * str1, const char * str2) {
  RoyString * string1 = roy_string_new_with_content(str1);
  RoyString * string2 = roy_string_new_with_content(str2);
  enum { BUF_SIZE = 7 };
  ROY_STR(buf, BUF_SIZE);
  int page1 = atoi(roy_string_regex(buf, string1, "\\d+\\)", 0));
  int page2 = atoi(roy_string_regex(buf, string2, "\\d+\\)", 0));
  roy_string_delete(string1);
  roy_string_delete(string2);
  return page1 - page2; // simple is good.
}

static int sectionValue(const char * str) {
  int ret = roy_parse_hexadecimal(str) * 10000;
  str = strpbrk(str, ".");
  if (str) {
    ret += atoi(++str) * 100;
  }
  if (str) {
    str = strpbrk(str, ".");
    if (str) {
      ret += atoi(++str);
    }
  }
  return ret;
}

int compSection(const char * str1, const char * str2) {
  RoyString * string1 = roy_string_new_with_content(str1);
  RoyString * string2 = roy_string_new_with_content(str2);
  enum { BUF_SIZE = 7 };
  ROY_STR(buf, BUF_SIZE);
  roy_string_regex(buf, string1, "[\\d\\.A-C]+\\]", 0);
  *(buf + strlen(buf) - 1) = '\0'; // trim ']' at tail.
  int section1 = sectionValue(buf);
  roy_string_regex(buf, string2, "[\\d\\.A-C]+\\]", 0);
  *(buf + strlen(buf) - 1) = '\0';
  int section2 = sectionValue(buf);
  roy_string_delete(string1);
  roy_string_delete(string2);
  return section1 - section2;
}

static char * strcpyd(char * dest, const char * src) {
  char * pdest = dest;
  const char * psrc = src;
  while (*psrc != '\0') {
    if (isalnum(*psrc) || isblank(*psrc)) {
      *pdest++ = *psrc;
    }
    psrc++;
  }
  return dest;
}

static int strcmpd(const char * str1, const char * str2) {
  ROY_STR(str1u, strlen(str1))
  strcpyd(str1u, str1);
  ROY_STR(str2u, strlen(str2))
  strcpyd(str2u, str2);
  return strcmp(str1u, str2u); 
}

int compIndex(const char * str1, const char * str2) {
  RoyString * string1 = roy_string_new_with_content(str1);
  RoyString * string2 = roy_string_new_with_content(str2);
  const char * str1t = str1 + roy_string_find_regex(string1, "\\]\\s.+", 0) + 2;
  const char * str2t = str2 + roy_string_find_regex(string2, "\\]\\s.+", 0) + 2;
  roy_string_delete(string1);
  roy_string_delete(string2);
  return strcmpd(str1t, str2t);
}

int compPageReverse(const char * str1, const char * str2) {
  return compPage(str2, str1);
}

int compSectionReverse(const char * str1, const char * str2) {
  return compSection(str2, str1);
}

int compIndexReverse(const char * str1, const char * str2) {
  return compIndex(str2, str1);
}
