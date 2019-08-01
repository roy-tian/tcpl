typedef double (* UnaryOperator)(double);
typedef double (* BinaryOperator)(double, double);

UnaryOperator strToUnaryOperator(const char *);
BinaryOperator strToBinaryOperator(const char *);