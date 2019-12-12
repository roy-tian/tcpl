
typedef struct Number_ {
  double value;
} Number;

Number * numberNew(double value);

Number * numberOperate(Number * dest, const Number * num1, const Number * num2, int operator_);