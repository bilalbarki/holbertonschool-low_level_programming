#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int print_char(char c);

int stdin_writer();
int reader(int *fp);
void incaseoferror(char *str);
int read_files(int argc, char *argv[]);

/*reproduces the behaviour 
  of the cat command*/
int main(int argc, char *argv[]){
  if (argc>1){
    if ( read_files(argc, argv) )
      return 1;
  }
  else{
    if ( stdin_writer() ){
      incaseoferror(argv[0]);
      perror("");
      return 1;
    }
  }
  return 0;
}

/*reads from stdin 
  and writes to stdout*/
int stdin_writer(){
  int i;
  char buf;
  while ( (i=read(0, &buf, 1)) ){
    if ( i==-1 || write(1, &buf, 1)==-1 )
      return 1;
  }
  return 0;
}

/*reads a file*/
int reader(int *fp){
  int i;
  char buf;
  while ( (i=read(*fp, &buf, 1)) ){
    if (i==-1) return 1;
    print_char(buf);
  }
  return 0;
}

void incaseoferror(char *str){
  for (;*str;str++) print_char(*str);
  print_char(':');
  print_char(' ');
}

/*reads filenames from arguments 
  passed to main and reads those files*/
int read_files(int argc, char *argv[]){
  int i, error;
  error=0;
  for (i=1;i<argc;i++){
    int fp;
    fp=open(argv[i], O_RDONLY);
    if ( fp == -1 ){
      incaseoferror(argv[0]);
      perror(argv[i]);
      error=1;
      continue;
    }
    if ( reader(&fp) ){
      incaseoferror(argv[0]);
      perror(argv[i]);
      /*close(fp);*/
      error=1;
    }
    close(fp);
  }
  return error;
}
