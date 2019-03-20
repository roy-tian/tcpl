#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 删除字符串 str 从 from 到 to 的所有字符
bool remove_between(char * str, int from, int to) {
    int length = strlen(str);
    int diff = to - from;
    if (from < 0 || from >= length || to < 0 || to >= length || diff < 0) {
        return false; // 参数不符合要求，返回操作失败。
    }
    int i = from;
    for (; i < length - diff - 1; i++) {
        str[i] = str[i + diff + 1]; // 依次向前挪动字符
    }
    str[length - diff - 1] = '\0'; // 截断字符串
    return true; // 操作成功
}


// 将字符串中所有出现的重复字符删除
void remove_repeat(char * str) {
    bool flag = false;      // 立 flag
    int p1 = 0, p2 = 1;     // 两个参考游标
    
    // 状态机
    while( ! (p1 == strlen(str) - 2 && p2 == strlen(str) - 1) && strlen(str) > 1) {
        if (flag == false && str[p1] != str[p2]) {
            p1++;
            p2++;
        } else if (flag == false && str[p1] == str[p2]) {
            flag = true;
            p2++;
        } else if (flag == true && str[p1] == str[p2]) {
            p2++;
        } else if (flag == true && str[p1] != str[p2]) {
            remove_between(str, p1, p2 - 1);
            flag = false;
            p1 = 0;
            p2 = 1;
        }
    }

    // 状态机运行完毕后，若存在最后两个重复字符是未处理的，处理它们。
    if (strlen(str) >= 2 && str[strlen(str)-1] == str[strlen(str)-2]) {
        remove_between(str, strlen(str) - 2, strlen(str) - 1);
    }
}


int main() {
    char s[100] = "bboookkeeppeasdferr";
    remove_repeat(s);
    puts(s); // easdfe
}