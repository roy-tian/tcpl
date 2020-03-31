#include "roy.h"

extern RoyString * content;

void pairPrint(const RoyPair * pair, bool * printZero);
RoyMap * populateKeytab(void);

RoyDeque * populateWordtab(void);
void add(const RoyMatch * match, RoyMap * keytab);