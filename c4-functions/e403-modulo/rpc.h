#ifndef E403_MODULO
#define E403_MODULO

#include "roy.h"

extern RoyMap * operators;

void populateOperators(void);

bool validNumber(const RoyString * token);
bool validBinary(const RoyString * token);
void binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, RoyString * operator_);

void rpc (RoyShell * shell);
void quit(RoyShell * shell);

#endif // E403_MODULO