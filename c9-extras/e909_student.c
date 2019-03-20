#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE_CAPACITY 100
#define STRING_CAPACITY 16

void for_every(void * array,
               int element_count,
               int element_size,
               void (*function)(void *)) {
    void * pointer = array;
    for (int i = 0; i != element_count; i++) {
        (*function)(array + i * element_size);
    }
}

typedef struct student {
    char name[STRING_CAPACITY];
    int age;
    char gender;
    char major[STRING_CAPACITY];
    int class_number;
    int score;
} student;

student base[BASE_CAPACITY];
int student_count = 0;

void set_student(student *destination,
                 char * name,
                 int age,
                 char gender,
                 char * major,
                 int class_number,
                 int score) {
    strcpy(destination->name, name);
    destination->age = age;
    destination->gender = gender;
    strcpy(destination->major, major);
    destination->class_number = class_number;
    destination->score = score;
}

student new_student(char * name,
                    int age,
                    char gender,
                    char * major,
                    int class_number,
                    int score) {
    student result;
    set_student(&result, name, age, gender, major, class_number, score);
    return result;
}

void copy_student(student * destination, student source) {
    set_student(destination,
                source.name,
                source.age,
                source.gender,
                source.major,
                source.class_number,
                source.score);
}

int add_a_student_to_base(student a_student) {
    if (student_count >= BASE_CAPACITY) {
        return 0;
    } else {
        copy_student(&base[student_count], a_student);
        student_count++;
        return 1;
    }
}

int remove_a_student_from_base_at(int index) {
    if (index >= student_count || index < 0) {
        return 0;
    } else {
        for (int i = index; i < student_count - 1; i++) {
            copy_student(&base[i], base[i + 1]);
        }
        student_count--;
        return 1;
    }
}

void print_student_table_title() {
    puts("  姓名            年龄 性别 班级               成绩");
    puts("---------------------------------------------------");
}

void print_student(student a_student) {
    int tab_name = STRING_CAPACITY - strlen(a_student.name) / 3 * 2;
    int tab_class = STRING_CAPACITY - strlen(a_student.major) / 3 * 2;
    printf("  %s", a_student.name);
    for (int i = 0; i != tab_name; i++) {
        putchar(' ');
    }
    printf("%d\t%s\t%s %02d 班",
           a_student.age,
           a_student.gender=='M' ? "男" : "女",
           a_student.major,
           a_student.class_number);
    for (int i = 0; i != tab_class; i++) {
        putchar(' ');
    }
    printf("%d", a_student.score);
}

void print_passed_student(void * a_student) {
    if ( (*(student *)a_student).score >= 60 ) {
        print_student(*(student *)a_student);
        putchar('\n');
    }
}

void print_every_student(void * a_student) {
    print_student(*(student *)a_student);
    putchar('\n');
}

void print(void (*function)(void *)) {
    print_student_table_title();
    for_every(base, student_count, sizeof(student), function);
    putchar('\n');
}

int student_score_compare(const void * student1, const void * student2) {
    int score1 = (*(const student *)student1).score;
    int score2 = (*(const student *)student2).score;
    return (score1 < score2) - (score1 > score2);
}

int main() {
    add_a_student_to_base(new_student("诸葛孔明", 18, 'M', "古筝", 1, 95));
    add_a_student_to_base(new_student("王朗", 19, 'M', "汉语言文学", 1, 59));
    add_a_student_to_base(new_student("梁非凡", 21, 'M', "警察管理", 2, 70));
    add_a_student_to_base(new_student("刘醒", 20, 'M', "侦查", 1, 80));
    add_a_student_to_base(new_student("比利海灵顿", 18, 'M', "体育教育", 2, 100));
    add_a_student_to_base(new_student("洛天依", 16, 'F', "声乐", 3, 98));
    add_a_student_to_base(new_student("雷军", 17, 'M', "计算机", 1, 88));
    add_a_student_to_base(new_student("王雪琴", 25, 'F', "建筑", 1, 50));
    add_a_student_to_base(new_student("葛平", 18, 'M', "播音主持", 4, 60));
    add_a_student_to_base(new_student("成龙", 25, 'M', "广告宣传", 1, 0));

    print(print_every_student);

    print(print_passed_student);

    qsort(base, student_count, sizeof(student), student_score_compare);

    print(print_every_student);
}
