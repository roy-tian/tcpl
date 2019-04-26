#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../../roylib/include/roystring.h"
#include "../../roylib/include/roydeque.h"

struct _Student {
  char name[STRING_CAPACITY];
  bool gender;
  unsigned score;
};

typedef struct _Student Student;

int next_rand(int min, int max) {
  return min + rand() / ((RAND_MAX + 1U) / max);
}

Student student_make(int student_index, int score) {
  Student ret;
  FILE * fp = fopen("namelist.txt", "r");
  char name[STRING_CAPACITY] = {'\0'};
  for (int i = 0; i != student_index; i++) {
    fgets(name, STRING_CAPACITY, fp);
  }
  strcpy(ret.name, name);
  *(ret.name + strlen(ret.name) - 1) = '\0';
  ret.gender = (student_index % 2 != 0);
  ret.score = score;
  return ret;
}

void student_print(Student * student) {
  printf("| %-11s %-4s %3d ",
         student->name,
         student->gender ? "Boy" : "Girl",
         student->score);
}

int main(void) {
  srand(time(NULL));
  RoyDeque * deque = roy_deque_new(sizeof(Student));
  for (int i = 0; i != 100; i++) {
    Student s = student_make(next_rand(0, 99), next_rand(0, 100));
    if ((i + 1) % 2 == 0) {
      roy_deque_push_front(deque, &s);
    } else {
      roy_deque_push_back(deque, &s);
    }
  }

  int len = roy_deque_length(deque);
  for (int i = 0; i != len; i++) {
    student_print(roy_deque_at(deque, Student, i));
    if ((i + 1) % 4 == 0) {
      printf("|\n");
    }
  }

  for (int i = 0; i != 50; i++) {
    if ((i + 1) % 2 == 0) {
      roy_deque_pop_front(deque);
    } else {
      roy_deque_pop_back(deque);
    }
  }

  len = roy_deque_length(deque);
  printf("====== %d\n", len);

  for (int i = 0; i != len; i++) {
    student_print(roy_deque_at(deque, Student, i));
    if ((i + 1) % 4 == 0) {
      printf("|\n");
    }
  }
}
