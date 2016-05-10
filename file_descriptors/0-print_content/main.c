#include <unistd.h>
#include <fcntl.h>

int print_char(char c);
int reader(int *fp);

/*prints the content of a file 
  on the standard output*/
int main(int argc, char *argv[]){
  int fp;
  if (argc!=2) return 1;
  fp=open(argv[1], O_RDONLY);
  if ( fp == -1 ) return 1;
  if ( reader(&fp) ){
    close(fp);
    return 1;
  }
  close(fp);
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
