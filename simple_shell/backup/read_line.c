#include <unistd.h>
#include <stdlib.h>

/*int print_char(char c);*/
void countletters(const int fb, int count, char **line, char check);
int print_char(char c);
/*prints the content of a file 
  on the standard output*/
char *read_line(const int fd){
  char *line;
  countletters(fd, 0,&line, '\0');
  return line;
}

/*counts letters and allocates space*/
void countletters(const int fb, int count, char **line, char check){
  char buf;
  if (read(fb, &buf, 1) && buf!='\n' /*&& check=='\0'*/){
      if(buf==34 || buf==39 || buf==96){
        if (check==buf) check='\0';
        else check=buf;
        countletters(fb, count+1, line, check);
      }
      else if (buf!='\b'){
        countletters(fb, count+1, line, check);
      }
      
      else{
        if (buf==34 || buf==39 || buf==96){
          if (check==buf) check='\0';
          else check=buf;
        }
        write(1, &buf, 1);
        countletters(fb, count, line, check);
      }
  }
  else if(check!='\0'){
    print_char('>');
    print_char(' ');
    /*check='\0';*/
    countletters(fb, count+1, line, check);
  }
  else{
    *line=malloc( sizeof(char)*(count+1) );
    (*line)[count]='\0';
    return;
  }
  (*line)[count]=buf;
}
