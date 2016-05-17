#include <stdlib.h>
int print_char(char c);

char *get_index(char *source, char character){
  for(;*source;source++){
    if (*source==character) return source;
  }
  return NULL;
}

void print_line(char *line){
  for (;*line;line++)
    print_char(*line);
}

int string_ncompare(const char *s, const char *t, int n) {
  for ( ; n--; s++, t++) {
    if(*s != *t) {
      return *s - *t;
    }
  }
  return 0;
}

int string_length(char *str){
  int length;
  for (length=0;str[length];length++);
  return length;
}
