#ifndef E403_CALC_H
#define E403_CALC_H

#include "roy.h"

bool validNumber(const RoyString * string);
bool validBinaryOperator(const RoyString * string);
void populateBinaryOperators(void);
RoyString * binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, RoyString * str);

void rpc (RoyShell * shell);
void quit(RoyShell * shell);

#endif // E403_CALC_H