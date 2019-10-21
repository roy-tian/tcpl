#include "roy.h"
#include <math.h>

typedef double (* BinaryOperator)(double, double);
typedef double (* UnaryOperator)(double);

void rpc(RoyShell *);
void quit(RoyShell *);

UnaryOperator unaryOperator(const RoyString *);
BinaryOperator binaryOperator(const RoyString *);

bool validNumber(const RoyString *);
bool validUnaryOperator(const RoyStack *, const RoyString *);
bool validBinaryOperator(const RoyStack *, const RoyString *);
bool tokenNotEnough(const RoyStack *, const RoyString *);
void doNumber(RoyStack *, const RoyString *);
void doUnaryOperate(RoyStack *, const RoyString *);
void doBinaryOperate(RoyStack *, const RoyString *);
void doError(RoyStack *, RoyString *, const char *);

double plus(double, double);
double minus(double, double);
double times(double, double);
double divide(double, double);
double modulo(double, double);

void
rpc(RoyShell * shell) {
  enum { CAPACITY = 128 };
  RoyStack * tokens = roy_stack_new(CAPACITY, sizeof(double));
  RoyString * token = roy_string_new();
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(token, roy_shell_argument_at(shell, i));
    if (validNumber(token)) {
      doNumber(tokens, token);
    } else if (validUnaryOperator(tokens, token)) {
      doUnaryOperate(tokens, token);
    } else if (validBinaryOperator(tokens, token)) {
      doBinaryOperate(tokens, token);
    } else if (tokenNotEnough(tokens, token)) {
      doError(tokens, token, "tokens not enough.");
      return;
    } else {
      roy_string_prepend_str(token, "unrecgonised token - \'");
      roy_string_append_str(token, "\'.");
      doError(tokens, token, roy_string_cstr(token));
      return;
    }
  }
  if (roy_stack_size(tokens) > 1) {
    doError(tokens, token, "parsing ends but stack not empty.");
    return;
  }
  printf("%.16g\n", *roy_stack_top(tokens, double));
  roy_string_delete(token);
  roy_stack_delete(tokens);
}

void
quit(RoyShell * shell) {
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

bool
validNumber(const RoyString * token) {
  return
  roy_string_match(token, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool
validUnaryOperator(const RoyStack  * tokens,
                   const RoyString * token) {
  return (unaryOperator(token) != NULL) && !roy_stack_empty(tokens);
}

bool
validBinaryOperator(const RoyStack  * tokens,
                    const RoyString * token) {
  return (binaryOperator(token) != NULL) && (roy_stack_size(tokens) >= 2);
}

bool
tokenNotEnough(const RoyStack  * tokens,
                               const RoyString * token) {
  return ( (unaryOperator(token) != NULL) && roy_stack_empty(tokens)) || 
         ((binaryOperator(token) != NULL) && (roy_stack_size(tokens) < 2));
}

UnaryOperator
unaryOperator(const RoyString * token) {
  if (roy_string_equal_str(token, "sin"))   { return sin; }
  if (roy_string_equal_str(token, "cos"))   { return cos; }
  if (roy_string_equal_str(token, "tan"))   { return tan; }
  if (roy_string_equal_str(token, "asin"))  { return asin; }
  if (roy_string_equal_str(token, "acos"))  { return acos; }
  if (roy_string_equal_str(token, "atan"))  { return atan; }
  if (roy_string_equal_str(token, "sqrt"))  { return sqrt; }
  if (roy_string_equal_str(token, "exp"))   { return exp; }
  if (roy_string_equal_str(token, "exp2"))  { return exp2; }
  if (roy_string_equal_str(token, "log"))   { return log; }
  if (roy_string_equal_str(token, "log10")) { return log10; }
  if (roy_string_equal_str(token, "log2"))  { return log2; }
  return NULL;
}

BinaryOperator
binaryOperator(const RoyString * token) {
  if (roy_string_equal_str(token, "+"))   { return plus; }
  if (roy_string_equal_str(token, "-"))   { return minus; }
  if (roy_string_equal_str(token, "*"))   { return times; }
  if (roy_string_equal_str(token, "/"))   { return divide; }
  if (roy_string_equal_str(token, "%"))   { return modulo; }
  if (roy_string_equal_str(token, "pow")) { return pow; }
  return NULL; 
}

void
doNumber(RoyStack        * tokens,
         const RoyString * token) {
  double value = atof(roy_string_cstr(token));
  roy_stack_push(tokens, &value);
}

void
doUnaryOperate(RoyStack        * tokens,
               const RoyString * token) {
  double operand = *roy_stack_top(tokens, double);
  roy_stack_pop(tokens);
  double result = unaryOperator(token)(operand);
  roy_stack_push(tokens, &result);
}

void
doBinaryOperate(RoyStack        * tokens,
                const RoyString * token) {
  double operand1 = *roy_stack_top(tokens, double);
  roy_stack_pop(tokens);
  double operand2 = *roy_stack_top(tokens, double);
  roy_stack_pop(tokens);
  double result = binaryOperator(token)(operand2, operand1);
  roy_stack_push(tokens, &result);
}

void
doError(RoyStack   * tokens,
        RoyString  * token,
        const char * errInfo) {
  printf("Syntax error: %s\n", errInfo);
  roy_string_delete(token);
  roy_stack_delete(tokens);
}

double plus(double operand1, double operand2) {
  return operand1 + operand2;
}

double minus(double operand1, double operand2) {
  return operand1 - operand2;
}

double times(double operand1, double operand2) {
  return operand1 * operand2;
}
double divide(double operand1, double operand2) {
  return operand1 / operand2;
}

double modulo(double operand1, double operand2) {
  return (double)((int)operand1 % (int)operand2);
}

int main(void) {
  RoyShell * shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}