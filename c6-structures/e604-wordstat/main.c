#include "roy.h"
#include "fq.h"

#define DELIMITER " ,.;:!?_()\n\"\'"

RoyUSet * stat(RoyString * content) {
  char * token = strtok(roy_string_str(content, 0), DELIMITER);
  RoyUSet * stattab = roy_uset_new(R_BUF_SIZE,
                                   roy_random_next(0, RAND_MAX),
                                   (RHash)fqHash,
                                   (RCompare)wordComp,
                                   NULL); // 'Fq's move to sorttab, need not delete here.
  while(token) {
    Fq * tmp = fqNew(token, 1);
    Fq * ins = (Fq *)roy_uset_find(stattab, tmp, strlen(tmp->word));
    // cast away 'const' doesn't matter: 'fqHash' doesn't involve 'count'.
    if (!ins) {
      roy_uset_insert(stattab, tmp, strlen(tmp->word));
    } else {
      fqDelete(tmp);
      fqAdd(ins);
    }
    token = strtok(NULL, DELIMITER);
  }
  return stattab;
}

void move(Fq * fq, RoyMSet ** sorttab) {
  roy_mset_insert(sorttab, fq, (RCompare)countComp);
}

int main(int argc, char ** argv) {
  roy_random_new();
  RoyString * content = roy_string_read_file(argv[1]);
  if (!content) {
    exit(EXIT_FAILURE);
  }

  RoyUSet * stattab = stat(content);
  RoyMSet * sorttab = roy_mset_new();
  roy_uset_for_each(stattab, (ROperate)move, &sorttab);
  roy_mset_for_each(sorttab, (ROperate)fqPrint, NULL);

  roy_mset_delete(sorttab, (ROperate)fqDelete, NULL);
  roy_uset_delete(stattab, NULL);
  roy_string_delete(content, NULL);
}