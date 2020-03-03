#include "syntax.h"

void setType(Type * shadow, size_t position, Type type) {
  *(shadow + position) = type;
}

void setTypeRange(Type * shadow, size_t from, size_t to, Type type) {
  for (size_t i = from; i < to; i++) {
    setType(shadow, i, type);
  }
}

Type getType(const Type * shadow, size_t position) {
  return *(shadow + position);
}

bool testType(const Type * shadow, size_t position, Type type) {
  return getType(shadow, position) == type;
}

bool testTypeRange(const Type * shadow, size_t from, size_t to, Type type) {
  for (size_t i = from; i < to; i++) {
    if (getType(shadow, i) != type) {
      return false;
    }
  }
  return true;
}

int findType(const Type * shadow, size_t from, size_t to, Type type) {
  for (size_t i = from; i < to; i++) {
    if (getType(shadow, i) == type) {
      return i;
    }
  }
  return -1; 
}
