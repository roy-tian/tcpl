#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

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
  return min + rand() % max;
  // return min + rand() / ((RAND_MAX + 1U) / max);
}

void populate(int * arr, int min, size_t max) {
  for (int i = 0; i != 100; i++) {
    *(arr + i) = next_random(min, max);
  }
} 

void print(const int * arr) {
  for (int i = 0; i != 100; i++) {
    printf("%5d", *(arr + i));
    if ((i + 1) % 10 == 0) {
      printf("\n");
    }
  }
}

int main(void) {
  srand(time(NULL));
  int array[100];
  populate(array, 0, 9999);
  int key = array[50];
  print(array);
  qsort(array, 100, sizeof(int), comp_int);
  printf("\n");
  print(array);
  printf("\n   STD METHOD: %d\n",
         *(const int *)bsearch (&key, array, 100, sizeof(int), comp_int));
  printf("CUSTOM METHOD: %d\n",
         *(const int *)bsearch_(&key, array, 100, sizeof(int), comp_int));
}