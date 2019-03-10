#include <wchar.h>

#define ROY_STRING_CAPACITY 1024
#define RoyStringInit(str, size) wchar_t (str)[(size)] = {'\0'}

typedef wchar_t * RoyString;