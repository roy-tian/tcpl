#ifndef E403_MODULO
#define E403_MODULO

#include "roy.h"

bool validNumber(const RoyString * string);
bool validBinaryOperator(const RoyString * string);
void populateBinaryOperators(void);
bool binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, RoyString * oper);

void rpc (RoyShell * shell);
void quit(RoyShell * shell);

#endif // E403_MODULO