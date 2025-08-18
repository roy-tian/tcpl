#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

enum {
  ARRAY_SIZE = 500,
  MAX        = 9999
};

void *
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
  return (comp(key, mid) == 0) ? (void *)mid : NULL;
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
  if (max < min) {
    return max;
  }
  int ret = max + 1;
  while (ret < min || ret > max) {
    ret = rand() / ((RAND_MAX + 1U) / (max - min + 1)) + min;
  }
  return ret;
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
    printf("%6d", *(arr + i));
    if ((i + 1) % 10 == 0) {
      printf("\n");
    }
  }
}

int main(void) {
  srand(time(NULL));
  int array[ARRAY_SIZE];
  populateArray(array, ARRAY_SIZE, 0, MAX);
  int key = array[ARRAY_SIZE / 2];

  printArray(array, ARRAY_SIZE);
  qsort(array, ARRAY_SIZE, sizeof(int), intComp);
  putchar('\n');
  printArray(array, ARRAY_SIZE);

  const int * found = bsearch(&key, array, ARRAY_SIZE, sizeof(int), intComp);
  printf("\n   STD METHOD FOUND %d AT POSITION %d.", key, found - array);

  found = bsearch_(&key, array, ARRAY_SIZE, sizeof(int), intComp);
  printf("\nCUSTOM METHOD FOUND %d AT POSITION %d.\n", key, found - array);

}