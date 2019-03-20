#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swap(int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int * array, int length) {
    for (int i = 0; i <= length / 2; i++) {
        swap(&array[i], &array[length - 1 - i]);
    }
}

int random_int(int min, int max) {
    return rand() % (max + 1) + min;
}

void shuffle(int * array, int length) {
    for (int i = 0; i != 10; i++) {
        swap(&array[random_int(0, length - 1)],
             &array[random_int(0, length - 1)]);
    }
}

void print(int * array, int length) {
    for (int i = 0; i != length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("orignal array:\n");
    print(array, 10);
    reverse(array, 10);
    printf("after \"reverse\" was called:\n");
    print(array, 10);
    shuffle(array, 10);
    printf("after \"shuffle\" was called:\n");
    print(array, 10);
}

