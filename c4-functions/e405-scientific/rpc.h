#ifndef E403_MODULO
#define E403_MODULO

#include "roy.h"

extern RoyMap * operators;

bool validNumber(const RoyString * token);
bool validBinary(const RoyString * token);
bool validUnary(const RoyString * token);
void populateOperators(void);
bool binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, RoyString * operator_);
bool unary(RoyString * dest, const RoyString * operand, RoyString * operator_);

void rpc (RoyShell * shell);
void quit(RoyShell * shell);

#endif // E403_MODULO