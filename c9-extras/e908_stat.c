#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// 统计字符的种类，共 27 种，0 - 25 为英文字母，26 为空格和标点符号。
#define KINDS_OF_CHAR 27

// 定义 charfq 类型，同时保存字符以及出现频率的数字。
typedef struct charfq {
    char character;
    int frequency;
} charfq;

// 设定 charfq 的函数：用 _character 和 _frequency 来设定一个 charfq
void set_charfq(charfq * _charfq, char _character, int _frequency) {
    _charfq->character = _character;
    _charfq->frequency = _frequency;
}

// 为 charfq 频率加 1 的函数
void charfq_frequency_increase(charfq * _charfq) {
    _charfq->frequency ++;
}

// 存放 charfq 的数组
charfq char_table[KINDS_OF_CHAR];

// 初始化 char_table 的函数
// 需在开始统计前调用。
void char_table_initial() {
    int i;
    for (i = 0; i < KINDS_OF_CHAR - 1; i++) {
        set_charfq(char_table + i, 'A' + i, 0);
    }
    set_charfq(char_table + i, '.', 0);
}

// 为 char_table 数组中第 index 个元素的 frequency 加 1
void char_table_increase_at(int index) {
    charfq_frequency_increase(char_table + index);
}

// 分别统计 string 中 27 种字符的个数，将结果保存在 char_table 中。
void stat(const char * string) {
    for (int i = 0; i < strlen(string); i++) {
        char current = string[i];
        if (islower(current))
            char_table_increase_at(current - 'a');
        if (isupper(current))
            char_table_increase_at(current - 'A');
        if (isspace(current) || ispunct(current)) // is punctuation
            char_table_increase_at(KINDS_OF_CHAR - 1);
    }
}

// 返回 char_table 中最大的那个频率。
int max_charfq_of_char_table() {
    int  max_fq = char_table[0].frequency;
    for (int i = 1; i < KINDS_OF_CHAR; i++) {
        if (max_fq < char_table[i].frequency) {
            max_fq = char_table[i].frequency;
        }
    }
    return max_fq;
}

// 返回 char_table 数组中非零频率的个数。
int count_non_zero_of_char_table() {
    int count = 0;
    for (int i = 0; i < KINDS_OF_CHAR; i++) {
        if (char_table[i].frequency != 0)
            count++;
    }
    return count;
}

// 比较两个 charfq 大小（每个字母出现次数多少）的函数，
// fq1 > fq2 返回 1，fq1 < fq2 返回 -1，相等返回 0。
// 将作为 qsort 的第四个参数。
int compare_charfq(const void * _charfq1, const void * _charfq2) {
    int fq1 = (*(const charfq *)_charfq1).frequency;
    int fq2 = (*(const charfq *)_charfq2).frequency;
    return (fq1 > fq2) - (fq1 < fq2);
}

// 打印垂直的频率直方图
void print_gram() {
    for (int i = max_charfq_of_char_table(); i > 0; i--) {
        for (int j = 0; j < KINDS_OF_CHAR; j++) {
            int current_char_count = char_table[j].frequency;
            if (current_char_count >= i)
                printf("* ");
            else if (current_char_count > 0 && current_char_count < i)
                printf("  ");
        }
        printf("\n");
    }
    // 此行以上绘制核心的直方图部分，以下是标题部分。
    for (int i = 0; i < count_non_zero_of_char_table() * 2 - 1; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < KINDS_OF_CHAR; i++) {
        if (char_table[i].frequency != 0) {
            printf("%c ", char_table[i].character);
        }
    }
}

int main() {
    char * str = "The quick brown fox jumps over the lazy dog.";
    char_table_initial();
    stat(str);
    qsort(char_table, KINDS_OF_CHAR, sizeof(charfq), compare_charfq);
    print_gram();
}