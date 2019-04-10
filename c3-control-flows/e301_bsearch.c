#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const void * bsearch_(const void * key,
                const void * ptr,
                size_t       count, 
                size_t       size,
                int (*comp)(const void *, const void *));

const void * bsearch_(const void * key,
                const void * ptr,
                size_t       count, 
                size_t       size,
                int (*comp)(const void *, const void *)) {
  const void * left = ptr;
  const void * mid;
  const void * right = ptr + (count - 1) * size;

    printf("P %d ", *(const int *)ptr);
    printf("L %d ", *(const int *)left);
    printf("R %d ", count);
  while (left <= right) {
    mid = ptr + (count / 2 - 1) * size;
    if (comp(key, mid) == 0) {
      return mid;
    } else {
      bsearch_(key, ptr, count / 2, size, comp);
      bsearch_(key, mid + size, count / 2, size, comp);
    }
  }
  return NULL;
}

int comp_int(const void * var1, const void * var2) {
  int val1 = *(const int *)var1;
  int val2 = *(const int *)var2;
  return (val1 > val2) - (val1 < val2);
}

int next_random(int min, size_t max) {
   return min + rand()/((RAND_MAX + 1U)/max);
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
  printf("\n%d\n", *(const int *)bsearch (&key, array, 100, sizeof(int), comp_int));
  printf("%d\n",   *(const int *)bsearch_(&key, array, 100, sizeof(int), comp_int));
}