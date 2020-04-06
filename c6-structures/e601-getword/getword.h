#include "roy.h"

extern RoyString * content;

#define RE_COMMENT      "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/"
#define RE_PREPROCESSOR "\\#include\\s+[\\\"\\<].+[\\\"\\>]|#(if|ifdef|ifndef|else|elif|endif|define|undef|include|error).*"
#define RE_TEXT         "\'.\'|\'\\\\[\'\"\\?\\\\abfnrtv0]\'|\"(?!\\\\\").*\""

void pairPrint(const RoyPair * pair, bool * printZero);
RoyMap * populateKeytab(void);

RoyDeque * populateWordtab(void);
void add(const RoyMatch * match, RoyMap * keytab);