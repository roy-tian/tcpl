#include "roy.h"

extern RoyString * content;
extern RoyDeque * matches;
extern int * shadow;
extern int * parentheses;
extern int * brackets;
extern int * braces;

#define NORMAL        0
#define COMMENT       1
#define PREPROCESSOR  2
#define TEXT          3
#define KEYWORD       4
#define TYPE          5
#define VARIABLE      6
#define NUMBER        7
#define BRACKET       8

#define ESCAPE        9
#define ERROR        10
#define BRACKET_1    11
#define BRACKET_2    12
#define BRACKET_3    13

#define RE_COMMENT      "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/"
#define RE_PREPROCESSOR "\\#include\\s+[\\\"\\<].+[\\\"\\>]|#(if|ifdef|ifndef|else|elif|endif|define|undef|include|error).*"
#define RE_TEXT         "\'.\'|\'\\\\[\'\"\\?\\\\abfnrtv0]\'|\"(?!\\\\\").*\""
#define RE_KEYWORD      "\\b(auto|break|case|const|continue|default|do|else|extern|for|goto|if|inline|register|restrict|return|sizeof|static|switch|typedef|volatile|while)\\b"
#define RE_TYPE         "\\b(char|double|enum|float|int|long|short|signed|struct|union|unsigned|void)\\b"
#define RE_VARIABLE     "[A-Za-z_]\\w*"
#define RE_NUMBER       "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?"
#define RE_BRACKET      "[\\{\\[\\(\\)\\]\\}]"

void lightup(const RoyMatch * match);

void colorize(const char * fileName);

int * newStack(void);
void deleteStack(int * stack);
int push(int * stack);
int pop(int * stack);