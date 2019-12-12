#include "number.h"
#include <stdio.h>

Number *
numberNew(double value) {
  Number * ret = (Number *)malloc(sizeof(Number));
  ret->value = value;
  return ret;
}

Number *
numberOperate(Number       * dest,
               const Number * num1,
               const Number * num2,
               int            operator_) {
  switch (operator_) {
  case '+': dest->value = num1->value + num2->value; break;
  case '-': dest->value = num1->value - num2->value; break;
  case '*': dest->value = num1->value * num2->value; break;
  case '/': dest->value = num1->value / num2->value; break;
  case '%': dest->value = (double)((int)num1->value % (int)num2->value); break;
  default: break;
  }
  return dest;
}