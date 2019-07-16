#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
  STRING_CAPACITY = 4095,
};

size_t countChar(const char * str, int ch);
size_t countLine(const char * str);
char * lineContent(char * line_content, const char * str, size_t line_number);
char * foldLine(char * str, size_t line_width);
char * fold(char * str, size_t line_width);

size_t
countChar(const char * str,
          int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t
countLine(const char * str) {
  size_t str_length = strlen(str);
  size_t count = countChar(str, '\n');
  if (str_length != 0 && *(str + str_length - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

char *
lineContent(char       * line_content,
            const char * str,
            size_t       line_number) {
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

char *
foldLine(char   * str,
         size_t   line_width) {
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

char *
fold(char   * str,
     size_t   line_width) {
  size_t str_length = strlen(str);
  char temp_str[STRING_CAPACITY + 1] = "\0";
  for (size_t i = 1; i <= countLine(str); i++) {
    char cur_line[STRING_CAPACITY + 1] = "\0";
    lineContent(cur_line, str, i);
    foldLine(cur_line, line_width);
    strcat(temp_str, "\n");
    strcat(temp_str, cur_line);
  } 
  strcpy(str, temp_str + 1);
  return str;
}

int main() {
  char str[STRING_CAPACITY + 1] =
  "Genghis Khan was the founder and first Great Khan of the Mongol Empire, which became the largest contiguous empire in history after his death. He came to power by uniting many of the nomadic tribes of Northeast Asia. After founding the Empire and being proclaimed \"Genghis Khan\", he launched the Mongol invasions that conquered most of Eurasia. Campaigns initiated in his lifetime include those against the Qara Khitai, Caucasus, and Khwarazmian, Western Xia and Jin dynasties. These campaigns were often accompanied by large-scale massacres of the civilian populations - especially in the Khwarazmian and Western Xia controlled lands. By the end of his life, the Mongol Empire occupied a substantial portion of Central Asia and China.\n\n"
  "Before Genghis Khan died he assigned Ögedei Khan as his successor. Later his        grandsons split his empire into khanates. Genghis Khan died in 1227 after defeating the Western Xia. By his request, his body was buried in an unmarked grave somewhere in Mongolia. His descendants extended the Mongol Empire across most of Eurasia by conquering or creating vassal states in all of modern-day China, Korea, the Caucasus, Central Asia, and substantial portions of Eastern Europe and Southwest Asia. Many of these invasions repeated the earlier large-scale slaughters of local populations. As a result, Genghis Khan and his empire have a fearsome reputation in local histories.\n\n"
  "Beyond his military accomplishments, Genghis Khan also advanced the Mongol \t\tEmpire in other ways. He decreed the adoption of the Uyghur script as the Mongol Empire's writing system. He also practiced meritocracy and encouraged religious tolerance in the Mongol Empire, and unified the nomadic tribes of Northeast Asia. Present-day Mongolians regard him as the founding father of Mongolia.\n\n"
  "Genghis Khan was known for the brutality of his campaigns, and is considered\t   \t by many to have been a genocidal ruler. However, he is also credited with bringing the Silk Road under one cohesive political environment. This brought relatively easy communication and trade between Northeast Asia, Muslim Southwest Asia, and Christian Europe, expanding the cultural horizons of all three areas.";
  FILE * fp = fopen("e122.txt", "w+");
  fputs("ORIGINAL STRING\n================\n", fp);
  fputs(str, fp);
  fputs("\n\nFOLDED STRING\n=============\n", fp);
  fputs(fold(str, 80), fp);
  fclose(fp);
}