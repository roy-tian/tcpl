#ifndef E403_DOUBLE_H
#define E403_DOUBLE_H

#include "roy.h"

RoyString * add(RoyString * dest, const RoyString * lhs, const RoyString * rhs);
RoyString * minus(RoyString * dest, const RoyString * lhs, const RoyString * rhs);
RoyString * times(RoyString * dest, const RoyString * lhs, const RoyString * rhs);
RoyString * divide(RoyString * dest, const RoyString * lhs, const RoyString * rhs);
RoyString * modulo(RoyString * dest, const RoyString * lhs, const RoyString * rhs);

RoyString * binary(RoyString * dest, const RoyString * lhs, const RoyString * rhs, const RoyString * operator_);

#endif // E403_DOUBLE_H