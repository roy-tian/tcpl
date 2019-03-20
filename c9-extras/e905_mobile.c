#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_string(char * array[], int length, char * string_to_find) {
    for (int i = 0; i != length; i++) {
        if (strcmp(array[i], string_to_find) == 0) {
            return i;
        }
    }
    return -1;
}

int carrier(char * number) {
    char first_3_chars[4];
    strncpy(first_3_chars, number, 3);
    char * cmcc[] = {"139", "138", "137", "136", "135", "134",
                     "159", "158", "157", "152", "151", "150",
                     "188", "187", "184", "183", "182",
                     "198", "178", "147"};
    char * cucc[] = {"130", "131", "132", "155", "156", "185", "186"
                     "145", "166", "176"};
    char * ctc[] =  {"133", "153", "173", "177", "180", "181", "189", "199"};
    if (find_string(cmcc, 19, first_3_chars) != -1) {
        return 1; // cmcc
    }
    if (find_string(cucc, 9, first_3_chars) != -1) {
        return 2; // cucc
    }
    if (find_string(ctc, 7, first_3_chars) != -1) {
        return 3; // ctc
    }
    return 0;
}

int valid(char * number) {
    if (strlen(number) != 11) {
        return 0;
    }
    if (carrier(number) == 0) {
        return 0;
    }
    for (int i = 3; i != 11; i++) {
        if (!isdigit(number[i])) {
            return 0;
        }
    }
    return 1;
}

void print(char * string) {
    char * flag;
    if (valid(string)) {
        switch(carrier(string)) {
        case 0:
            flag = "not a";
            break;
        case 1:
            flag = "a CMCC";
            break;
        case 2:
            flag = "a CUCC";
            break;
        case 3:
            flag = "a CTC";
            break;
        default:
            break;
        }
    } else {
        flag = "not a";
    }
    printf("%s is %s mobile phone number.\n", string, flag);
}

int main() {
    print("13930681339");
    print("13363638266");
    print("10861600123");
    print("238abcdefgh");
    print("13哎呀我操哎呀我日");
}