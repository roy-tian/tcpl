#ifndef RPC_H
#define RPC_H

#include "roy.h"

void rpc(RoyShell *);
void quit(RoyShell *);

bool validNumber(const RoyString *);
bool validOperator(const RoyString *);
void doNumber(RoyStack *, const RoyString *);
void doOperate(RoyStack *, const RoyString *);
void doError(RoyStack *, RoyString *, const char *);

#endif // RPC_H