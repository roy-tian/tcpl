#include "../../roylib/roy.h"

struct _Student {
  char     name[STRING_CAPACITY];
  bool     gender;
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
  for (int i = 0; i <= student_index; i++) {
    fgets(name, STRING_CAPACITY, fp);
  }
  strcpy(ret.name, name);
  *(ret.name + strlen(ret.name) - 1) = '\0';
  ret.gender = !(student_index % 2);
  ret.score = score;
  fclose(fp);
  return ret;
}

void student_print(const Student * student) {
  printf("%-11s %-4s %3d\n",
         student->name,
         student->gender ? "Boy" : "Girl",
         student->score);
}

int student_compare(const Student * student1, const Student * student2) {
  return (student1->score > student2->score) -
         (student1->score < student2->score);
}

bool student_qualified(const Student * student) {
  return student->score >= 60;
}

int main(void) {
  srand(time(NULL));
  RoyMSet * set = NULL;
  for (int i = 1; i != 1001; i++) {
    Student s = student_make(next_rand(0, 99), next_rand(0, 100));
    roy_mset_insert(&set, &s, sizeof(Student), ROY_COMPARE(student_compare));
  }
  roy_mset_for_each(set, ROY_OPERATE(student_print));

  student_print(roy_mset_const_max(set)->key);
}
