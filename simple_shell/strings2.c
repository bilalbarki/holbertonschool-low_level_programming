#include <stdlib.h>
int print_char(char c);

/*gets index for the character given*/
char *get_index(char *source, char character){
  for(;*source;source++){
    if (*source==character) return source;
  }
  return NULL;
}

/*prints line*/
void print_line(char *line){
  for (;*line;line++)
    print_char(*line);
}

/*strncmp*/
int string_ncompare(const char *s, const char *t, int n) {
  for ( ; n--; s++, t++) {
    if(*s != *t) {
      return *s - *t;
    }
  }
  return 0;
}

/*returns string length*/
int string_length(char *str){
  int length;
  for (length=0;str[length];length++);
  return length;
}
