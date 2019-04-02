#ifndef ROYNUMBER_H
#define ROYNUMBER_H

typedef unsigned long RoyUInteger;
typedef long RoyInteger;
typedef double RoyReal;

// Converts 'str' of hexadecimal digits into its equivalent value.
RoyUInteger roy_parse_hexadecimal(const char * str);

char * roy_to_string_binary(RoyUInteger num);

#endif // ROYNUMBER_H