#ifndef E403_MODULO
#define E403_MODULO

#include "roy.h"

extern RoyMap * operators;

typedef double (* Binary)(double, double);

void populate(void);

bool validNumber(const RoyString * token);
bool validBinary(const RoyString * token);
void binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, const RoyString * operator_);

void rpc (RoyShell * shell);
void quit(RoyShell * shell);

#endif // E403_MODULO