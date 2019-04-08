#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_CAPACITY 1023
#define STRING_CAPACITY_HUGE 65535
#define WIDTH 80
#define ROY_STRING(str, size)\
        char str[size + 1];\
        memset(str, '\0', size + 1);

size_t roy_string_count_char(const char * str, int ch);
size_t roy_string_count_line(const char * str);
char * roy_string_line(char * line_content,
                       const char * str,
                       size_t line_number);
char * roy_string_fold_line(char * str, size_t line_width);
char * roy_string_fold(char * str, size_t line_width);

size_t roy_string_count_char(const char * str, int ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t roy_string_count_line(const char * str) {
  size_t str_length = strlen(str);
  size_t count = roy_string_count_char(str, '\n');
  if (str_length != 0 && *(str + str_length - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

char * roy_string_line(char * line_content,
                       const char * str,
                       size_t line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * str_tail = strchr(str, '\n');
  if (!str_tail) {
    strcpy(line_content, str);
  } else {
    strncpy(line_content, str, str_tail - str);
  }
  return line_content;
}

char * roy_string_fold_line(char * str, size_t line_width) {
  char * pstr = str;
  while (strlen(pstr) > line_width) {    
    pstr += line_width - 1;
    if(isblank(*(pstr + 1))) {
      while (isblank(*(pstr++ + 1))) {  }
      *(pstr - 1) = '\n';
    } else {
      if (!isblank(*pstr)) {
        while (!isblank(*(pstr-- - 1))) {  }
      }
      *pstr++ = '\n';
    }
  }
  return str;
}

char * roy_string_fold(char * str, size_t line_width) {
  size_t str_length = strlen(str);
  ROY_STRING(temp_str, str_length);
  for (size_t i = 1; i <= roy_string_count_line(str); i++) {
    ROY_STRING(cur_line, str_length);
    roy_string_line(cur_line, str, i);
    roy_string_fold_line(cur_line, line_width);
    strcat(temp_str, "\n");
    strcat(temp_str, cur_line);
  } 
  strcpy(str, temp_str + 1);
  return str;
}

int main() {
  ROY_STRING(str, STRING_CAPACITY_HUGE)
  strcpy(str, "Genghis Khan was the founder and first Great Khan of the Mongol Empire, which became the largest contiguous empire in history after his death. He came to power by uniting many of the nomadic tribes of Northeast Asia. After founding the Empire and being proclaimed \"Genghis Khan\", he launched the Mongol invasions that conquered most of Eurasia. Campaigns initiated in his lifetime include those against the Qara Khitai, Caucasus, and Khwarazmian, Western Xia and Jin dynasties. These campaigns were often accompanied by large-scale massacres of the civilian populations - especially in the Khwarazmian and Western Xia controlled lands. By the end of his life, the Mongol Empire occupied a substantial portion of Central Asia and China.\n\n");
  strcat(str, "Before Genghis Khan died he assigned Ögedei Khan as his successor. Later his        grandsons split his empire into khanates. Genghis Khan died in 1227 after defeating the Western Xia. By his request, his body was buried in an unmarked grave somewhere in Mongolia. His descendants extended the Mongol Empire across most of Eurasia by conquering or creating vassal states in all of modern-day China, Korea, the Caucasus, Central Asia, and substantial portions of Eastern Europe and Southwest Asia. Many of these invasions repeated the earlier large-scale slaughters of local populations. As a result, Genghis Khan and his empire have a fearsome reputation in local histories.\n\n");
  strcat(str, "Beyond his military accomplishments, Genghis Khan also advanced the Mongol \t\tEmpire in other ways. He decreed the adoption of the Uyghur script as the Mongol Empire's writing system. He also practiced meritocracy and encouraged religious tolerance in the Mongol Empire, and unified the nomadic tribes of Northeast Asia. Present-day Mongolians regard him as the founding father of Mongolia.\n\n");
  strcat(str, "Genghis Khan was known for the brutality of his campaigns, and is considered\t   \t by many to have been a genocidal ruler. However, he is also credited with bringing the Silk Road under one cohesive political environment. This brought relatively easy communication and trade between Northeast Asia, Muslim Southwest Asia, and Christian Europe, expanding the cultural horizons of all three areas.");
  FILE * fp = fopen("e122.txt", "w+");
  fputs("ORIGINAL STRING\n================\n", fp);
  fputs(str, fp);
  fputs("\n\nFOLDED STRING\n=============\n", fp);
  fputs(roy_string_fold(str, WIDTH), fp);
  fclose(fp);
}