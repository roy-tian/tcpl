#ifndef ROYSTRING_H
#define ROYSTRING_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

char * roy_string_to_lower(char * str);

char * roy_string_to_upper(char * str);

char * roy_string_reverse(char * str);

char * roy_string_unique_char(char * str, int ch);

char * roy_string_replace_all(char * str,
                              const char * old_sub,
                              const char * new_sub);

char * roy_string_replace_index(char * str,
                                size_t old_sub_pos,
                                size_t old_sub_len,
                                const char * new_sub);

char * roy_string_get_line(char * dest,
                           const char * src,
                           size_t line_number);

char * roy_string_trim_line(char * str);

char * roy_string_trim(char * str);

char * roy_string_detab(char * str, size_t tab_size);

char * roy_string_entab(char * str, size_t tab_size);

size_t roy_string_count_char(const char * str, int ch);

size_t roy_string_count_char_if(const char * str,
                                int (*condition)(int));

size_t roy_string_count_substring(const char * str,
                                  const char * sub,
                                  bool sensibility);

size_t roy_string_count_word(const char * str);

size_t roy_string_count_word_if(const char * str, size_t length);

size_t roy_string_count_line(const char * str);

size_t roy_string_line_length(const char * str, size_t line_number);

#endif // ROYSTRING_H
