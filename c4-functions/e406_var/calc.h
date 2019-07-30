typedef double (* UnaryOperator)(double);
typedef double (* BinaryOperator)(double, double);

UnaryOperator charToUnaryOperator(const char *);

BinaryOperator charToBinaryOperator(const char *);

double plus(double, double);
double minus(double, double);
double times(double, double);
double divide(double, double);
double modulo(double, double);
