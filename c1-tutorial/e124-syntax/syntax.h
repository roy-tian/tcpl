#include "roy.h"

typedef enum {
  NORMAL,
  COMMENT,
  TEXT,
  ESCAPE,
  BRACKET_1,
  BRACKET_2,
  BRACKET_3,
  ERROR
} Type;

enum {
  BUFFER_SIZE = 0x100
};

void setType      (      Type * shadow, size_t position, Type type);
void setTypeRange (      Type * shadow, size_t from, size_t to, Type type);
Type getType      (const Type * shadow, size_t position);
bool testType     (const Type * shadow, size_t position, Type type);
bool testTypeRange(const Type * shadow, size_t from, size_t to, Type type);
int  findType     (const Type * shadow, size_t from, size_t to, Type type);

Type * newStack(void);
void deleteStack(Type * stack);
Type push(Type * stack);
Type pop(Type * stack);

void tokenize(Type * shadow, const RoyString * content);

size_t read(RoyString * dest, const char * path);
void write(const Type * shadow, const RoyString * content, const char * path);