#ifndef E604_FQ_H
#define E604_FQ_H

typedef struct Fq_ {
  char * word;
  int    count;
} Fq;

Fq * fqNew(const char * word, int count);
void fqDelete(Fq * fq);
void fqPrint(const Fq * fq);
void fqAdd(Fq * fq);
uint64_t fqHash(const Fq * fq, size_t size, uint64_t seed);
int wordComp(const Fq * lhs, const Fq * rhs);
int countComp(const Fq * lhs, const Fq * rhs);


#endif // E604_FQ_H