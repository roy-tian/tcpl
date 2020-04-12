#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash/hash.h"
#include "fq.h"

Fq * fqNew(const char * word, int count) {
  Fq * ret = malloc(sizeof(Fq));
  ret->count = count;
  ret->word = calloc(strlen(word) + 1, sizeof(char));
  strcpy(ret->word, word);
  return ret;
}

void fqDelete(Fq * fq) {
  free(fq->word);
  free(fq);
}

void fqPrint(const Fq * fq) {
  printf("%5d %s\n", fq->count, fq->word);
}

void fqAdd(Fq * fq) {
  fq->count++;
}

uint64_t fqHash(const Fq * fq, size_t size, uint64_t seed) {
  return MurmurHash2(fq->word, size, seed);
}

int wordComp(const Fq * lhs, const Fq * rhs) {
  return strcmp(lhs->word, rhs->word);
}

int countComp(const Fq * lhs, const Fq * rhs) {
  return (lhs->count > rhs->count) - (lhs->count < rhs->count);
}
