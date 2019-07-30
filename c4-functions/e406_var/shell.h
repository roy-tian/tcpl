#include "roy.h"
#include "calc.h"

extern RoyShell * shell;
extern RoyStack * stackOperand;
extern RoyVector * vectorVariable;

void rpc(RoyShell *);
void quit(RoyShell *);

bool validNumber(RoyString * arg);
bool validVariable(RoyString * arg);
UnaryOperator validUnaryOperator(RoyString * arg);
BinaryOperator validBinaryOperator(RoyString * arg);

void doNumber(RoyString * arg);
void doVariable(RoyString * arg);
void doUnaryOperator(const UnaryOperator op);
void doBinaryOperator(const BinaryOperator op);
void doError(void);
