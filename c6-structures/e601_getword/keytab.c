#include "getword.h"

static void pairInsert(RoyString * string, RoyMap * map);
static void pairDelete(RoyPair * pair, void * user_data);
static int  pairComp(const RoyPair * lhs, const RoyPair * rhs);

RoyMap * populateKeytab(void) {
  RoyMap * ret = roy_map_new((RCompare)pairComp, (ROperate)pairDelete);
  RoyString * content = roy_string_read_file("keytab");
  RoyDeque * keyDeque = roy_deque_new((ROperate)roy_string_delete);
  roy_string_split(keyDeque, content, "\n");
  roy_deque_for_each(keyDeque, (ROperate)pairInsert, ret);

  roy_string_delete(content, NULL);
  roy_deque_delete(keyDeque, NULL);
  return ret;
}

void pairPrint(const RoyPair * pair, bool * printZero) {
  const char * name = roy_string_cstr(pair->key, 0);
  size_t count = *(size_t*)pair->value;
  if (*printZero && count) {
    printf("%3zu '%s'%s", count, name, (count <= 1) ? "\n" : "s\n" );
  }
}

static void pairInsert(RoyString * string, RoyMap * map) {
  int * count = calloc(1, sizeof(int)); // will be freed inside 'pairDelete'.
  roy_map_insert(map, roy_string_copy(string), count);
}

static void pairDelete(RoyPair * pair, void * user_data) {
  roy_string_delete(pair->key, user_data);
  free(pair->value);
  free(pair);
}

static int pairComp(const RoyPair * lhs, const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}