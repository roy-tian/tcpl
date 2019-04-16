#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define ELEMENT_COUNT 200

const void * bsearch_(const void * key,
                      const void * ptr,
                      size_t       count, 
                      size_t       size,
                      int       (* comp)(const void *, const void *));
int comp_int(const void * var1, const void * var2);
int next_random(int min, int max);
void populate(int * arr, int min, size_t max);
void print(const int * arr);


const void * bsearch_(const void * key,
                      const void * ptr,
                      size_t       count, 
                      size_t       size,
                      int       (* comp)(const void *, const void *)) {
  const void * right = ptr + (count - 1) * size;
  const void * mid = ptr + (count - 1) / 2 * size;

  while (comp(ptr, right) <= 0 && comp(key, mid) != 0) {
    count /= 2;
    if (comp(key, mid) < 0) {
      right = mid - size;
    } else /* if (comp(key, mid) > 0) */ {
      ptr = mid + size;
    }
    mid = ptr + (count - 1) / 2 * size;
  }
  return (comp(key, mid) == 0) ? mid : NULL;
}

int comp_int(const void * var1, const void * var2) {
  int val1 = *(const int *)var1;
  int val2 = *(const int *)var2;
  return (val1 > val2) - (val1 < val2);
}

int next_random(int min, int max) {
  if (RAND_MAX == INT_MAX) {
    return min + rand() / ((RAND_MAX + 1U) / max);
  }
  return min + rand() % max;
}

void populate(int * arr, int min, size_t max) {
  for (int i = 0; i != ELEMENT_COUNT; i++) {
    *(arr + i) = next_random(min, max);
  }
} 

void print(const int * arr) {
  for (int i = 0; i != ELEMENT_COUNT; i++) {
    printf("%5d", *(arr + i));
    if ((i + 1) % 10 == 0) {
      printf("\n");
    }
  }
}

int main(void) {
  srand(time(NULL));
  int array[ELEMENT_COUNT];
  populate(array, 0, 9999);
  int key = array[ELEMENT_COUNT / 2];
  print(array);
  qsort(array, sizeof array / sizeof *array, sizeof *array, comp_int);
  printf("\n");
  print(array);
  printf("\n   STD METHOD: %d\n",
         *(const int *)bsearch (&key, array,
                                sizeof array / sizeof *array, sizeof *array,
                                comp_int));
  printf("CUSTOM METHOD: %d\n",
         *(const int *)bsearch_(&key, array,
                                sizeof array / sizeof *array, sizeof *array,
                                comp_int));
}