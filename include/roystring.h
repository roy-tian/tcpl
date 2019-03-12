#ifndef ROYSTRING_H
#define ROYSTRING_H

#include <stdbool.h>
#include <stdlib.h>

typedef int RoyChar;
typedef char * RoyString;
typedef char * RoyStringIter;

RoyString roy_string_new(RoyString str, size_t size);
RoyString roy_string_new_with_content(RoyString str, const RoyString content);
void      roy_string_delete(RoyString str);
RoyString roy_string_copy(RoyString dest, const RoyString src);
RoyString roy_string_concatenate(RoyString dest, const RoyString src);
RoyString roy_string_to_lower(RoyString str);
RoyString roy_string_to_upper(RoyString str);
RoyString roy_string_unique_char(RoyString str, RoyChar ch);
RoyString roy_string_replace_all(RoyString str, const RoyString old_sub, const RoyString new_sub);

int roy_string_count_char(const RoyString str, RoyChar ch);
int roy_string_count_char_if(const RoyString str, bool (*condition)(RoyChar));
int roy_string_count_substring(const RoyString str, const RoyString sub);
int roy_string_count_substring_if(const RoyString str, bool (*condition)(RoyString));
int roy_string_count_substring_insensitively(const RoyString str, const RoyString sub);

#endif // ROYSTRING_H
