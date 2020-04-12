#ifndef E603_CROSSREF_H
#define E603_CROSSREF_H

#include "roy.h"

#define WORD    2
#define NEWLINE 3
#define RE_NOISEWORD "\\b([Aa]|[Aa]n|[Tt]he|[Aa]re|[Ii]n|[Ii]s|[Oo]f|[Oo]r|[Tt]hat|[Tt]he|[Tt]his|[Tt]o)\\b"
#define RE_WORD "\\b(\\w|’)+\\b"
#define RE_NEWLINE "\\n"

// This is why we need lambda expressions.
typedef struct Pack_ {
  int               index;
  RoyMap          * wordtab;
  const RoyString * content;
} Pack;

void stat(const RoyMatch * match, Pack * pack);

int pairCompare(const RoyPair * lhs, const RoyPair * rhs);
void pairDelete(RoyPair * pair);
void pairPrint(const RoyPair * pair);

#endif // E603_CROSSREF_H