#ifndef E403_MODULO
#define E403_MODULO

#include "roy.h"

extern RoyMap * operators;

typedef double (* Binary)(double, double);
typedef double (* Unary)(double);

void populate(void);

bool validNumber(const RoyString * token);
bool validBinary(const RoyString * token);
bool validUnary(const RoyString * token);
void binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, const RoyString * operator_);
void unary(RoyString * dest, const RoyString * operand, const RoyString * operator_);

void rpc(RoyDeque * args);

#endif // E403_MODULO