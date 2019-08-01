#include "roy.h"
#include "calc.h"

extern RoyShell * shell;
extern RoyStack * operands;
extern RoyMap * variables;

void rpc(RoyShell *);
void playback(RoyShell *);
void quit(RoyShell *);
