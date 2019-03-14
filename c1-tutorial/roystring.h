#ifndef ROYSTRING_H
#define ROYSTRING_H

#include <stdbool.h>

char * roy_string_to_lower(char * str);

char * roy_string_to_upper(char * str);

char * roy_string_trim(char * str);

char * roy_string_unique_char(char * str, int ch);

char * roy_string_replace_all(char * str,
                              const char * old_sub,
                              const char * new_sub);



int roy_string_count_char(const char * str, int ch);

int roy_string_count_char_if(const char * str,
                             int (*condition)(int));

int roy_string_count_substring(const char * str,
                               const char * sub,
                               bool sensibility);

int roy_string_count_word(const char * str);

int roy_string_count_word_if(const char * str, int length);

int roy_string_count_line(const char * str);

int roy_string_line_length(const char * str, int line_number);

char * roy_string_get_line(char * dest,
                           const char * src,
                           int line_number);

#endif // ROYSTRING_H
