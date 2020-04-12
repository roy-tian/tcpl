#ifndef E602_VARSTAT_H
#define E602_VARSTAT_H

#include "roy.h"

#define VARIABLE 5
#define DEFAULT_NSAME 3

#define RE_COMMENT      "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/"
#define RE_PREPROCESSOR "\\#include\\s+[\\\"\\<].+[\\\"\\>]|#(if|ifdef|ifndef|else|elif|endif|define|undef|include|error).*"
#define RE_TEXT         "\'.\'|\'\\\\[\'\"\\?\\\\abfnrtv0]\'|\"(?!\\\\\").*\""
#define RE_KEYWORD      "\\b(auto|break|case|const|continue|default|do|else|extern|for|goto|if|inline|register|restrict|return|sizeof|static|switch|typedef|volatile|while|char|double|enum|float|int|long|short|signed|struct|union|unsigned|void)\\b"
#define RE_VARIABLE     "[A-Za-z_]\\w*"

extern RoyString * content;
extern int nsame;

bool parseArgs(int argc, char ** restrict argv, const char ** restrict fileName, int * restrict nsame_);
int pairComp(const RoyPair * lhs, const RoyPair * rhs);
void pairDelete(RoyPair * pair);

void add(const RoyMatch * match, RoyMap * vars);
bool var(const RoyMatch * match);

void printVarTable(const RoyPair * pair);

#endif // E602_VARSTAT_H