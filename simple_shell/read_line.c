#include <unistd.h>
#include <stdlib.h>

/*int print_char(char c);*/
void countletters(const int fb, int count, char **line);

/*prints the content of a file 
  on the standard output*/
char *read_line(const int fd){
  char *line;
  countletters(fd, 0,&line);
  return line;
}

/*counts letters and allocates space*/
void countletters(const int fb, int count, char **line){
  char buf;
  if (read(fb, &buf, 1) && buf!='\n'){
      countletters(fb, count+1, line);
  }
  else{
    *line=malloc( sizeof(char)*(count+1) );
    (*line)[count]='\0';
    return;
  }
  (*line)[count]=buf;
}
