#include "roystring.h"
#include <stdio.h>

#define STRING_CAPACITY 8192
#define WIDTH 80

int main() {
  FILE* fp = fopen("e122.txt", "w+");
  ROY_STRING(str, STRING_CAPACITY)
  strcpy(str, "Genghis Khan was the founder and first Great Khan of the Mongol Empire, which became the largest contiguous empire in history after his death. He came to power by uniting many of the nomadic tribes of Northeast Asia. After founding the Empire and being proclaimed \"Genghis Khan\", he launched the Mongol invasions that conquered most of Eurasia. Campaigns initiated in his lifetime include those against the Qara Khitai, Caucasus, and Khwarazmian, Western Xia and Jin dynasties. These campaigns were often accompanied by large-scale massacres of the civilian populations - especially in the Khwarazmian and Western Xia controlled lands. By the end of his life, the Mongol Empire occupied a substantial portion of Central Asia and China.\n\n");
  strcat(str, "Before Genghis Khan died he assigned Ögedei Khan as his successor. Later his        grandsons split his empire into khanates. Genghis Khan died in 1227 after defeating the Western Xia. By his request, his body was buried in an unmarked grave somewhere in Mongolia. His descendants extended the Mongol Empire across most of Eurasia by conquering or creating vassal states in all of modern-day China, Korea, the Caucasus, Central Asia, and substantial portions of Eastern Europe and Southwest Asia. Many of these invasions repeated the earlier large-scale slaughters of local populations. As a result, Genghis Khan and his empire have a fearsome reputation in local histories.\n\n");
  strcat(str, "Beyond his military accomplishments, Genghis Khan also advanced the Mongol \t\tEmpire in other ways. He decreed the adoption of the Uyghur script as the Mongol Empire's writing system. He also practiced meritocracy and encouraged religious tolerance in the Mongol Empire, and unified the nomadic tribes of Northeast Asia. Present-day Mongolians regard him as the founding father of Mongolia.\n\n");
  strcat(str, "Genghis Khan was known for the brutality of his campaigns, and is considered\t   \t by many to have been a genocidal ruler. However, he is also credited with bringing the Silk Road under one cohesive political environment. This brought relatively easy communication and trade between Northeast Asia, Muslim Southwest Asia, and Christian Europe, expanding the cultural horizons of all three areas.");
  fprintf(fp, "ORIGINAL STRING\n%s", str);
  fprintf(fp, "\n\n-----------\nFOLDED STRING\n%s", roy_string_fold(str, WIDTH));
}