#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

const void * bsearch_(const void * key, const void * ptr, size_t count, size_t size, int (* comp)(const void *, const void *));
int intComp(const void * var1, const void * var2);
int nextRandom(int min, int max);
void populateArray(int * arr, size_t size, int min, int max);
void printArray(const int * arr, size_t size);

const void *
bsearch_(const void * key,
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

int
intComp(const void * var1,
        const void * var2) {
  int val1 = *(const int *)var1;
  int val2 = *(const int *)var2;
  return (val1 > val2) - (val1 < val2);
}

int
nextRandom(int min,
           int max) {
  if (RAND_MAX == INT_MAX) {
    return min + rand() / ((RAND_MAX + 1U) / max);
  }
  return min + rand() % max;
}

void
populateArray(int    * arr,
              size_t   size,
              int      min,
              int      max) {
  for (int i = 0; i != size; i++) {
    *(arr + i) = nextRandom(min, max);
  }
} 

void
printArray(const int * arr,
           size_t      size) {
  for (int i = 0; i != size; i++) {
    printf("%5d", *(arr + i));
    if ((i + 1) % 10 == 0) {
      printf("\n");
    }
  }
}

int main(void) {
  enum {ARRAY_SIZE = 200, MAX = 9999};
  srand(time(NULL));
  int array[ARRAY_SIZE];
  populateArray(array, ARRAY_SIZE, 0, MAX);
  int key = array[ARRAY_SIZE / 2];
  printArray(array, ARRAY_SIZE);
  qsort(array, sizeof array / sizeof *array, sizeof *array, intComp);
  printf("\n");
  printArray(array, ARRAY_SIZE);
  printf("\n   STD METHOD: %d\n",
         *(const int *)bsearch (&key,
                                array,
                                sizeof array / sizeof *array,
                                sizeof *array,
                                intComp));
  printf("CUSTOM METHOD: %d\n",
         *(const int *)bsearch_(&key,
                                array,
                                sizeof array / sizeof *array,
                                sizeof *array,
                                intComp));
}