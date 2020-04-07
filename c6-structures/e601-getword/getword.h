#include "roy.h"

#define RE_COMMENT      "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/"
#define RE_PREPROCESSOR "\\#include\\s+[\\\"\\<].+[\\\"\\>]|#(if|ifdef|ifndef|else|elif|endif|define|undef|include|error).*"
#define RE_TEXT         "\'.\'|\'\\\\[\'\"\\?\\\\abfnrtv0]\'|\"(?!\\\\\").*\""
#define RE_VARIABLE     "[A-Za-z_]\\w*"

extern RoyString * content;

RoyMap * populateKeytab(void);

void pairPrint(const RoyPair * pair, bool * printZero);

RoyDeque * populateWordtab(void);

void add(const RoyMatch * match, RoyMap * keytab);