#ifndef ROYNUMBER_H
#define ROYNUMBER_H

typedef unsigned long RoyUInteger;
typedef long RoyInteger;
typedef double RoyReal;

// Converts 'str' of hexadecimal digits into its equivalent value.
RoyUInteger roy_parse_hexadecimal(const char * str);

char * roy_number_to_string_binary(char * dest, RoyUInteger num);

char * roy_number_to_string_hexadecimal(char * dest, RoyUInteger num);

char * roy_number_to_string_decimal(char * dest, RoyInteger num);

char * roy_number_to_string(char * dest, RoyReal num);

#endif // ROYNUMBER_H