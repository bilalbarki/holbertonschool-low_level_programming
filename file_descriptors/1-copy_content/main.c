#include <unistd.h>
#include <fcntl.h>

int print_char(char c);
int copier(int *dest, int *source);

int main(int argc, char *argv[]){
  int fr, fw;
  if (argc!=3) return 1;
  fr=open(argv[1], O_RDONLY);
  if ( fr == -1 ) return 1;
  fw=open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 
	  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if ( fw == -1 ){
    close(fr);
    return 1;
  }
  if ( copier(&fw, &fr) ){
    close(fr);
    close(fw);
    return 1;
  }
  close(fr);
  close(fw);
  return 0;
}

int copier(int *dest, int *source){
  int i;
  char buf;
  while ( (i=read(*source, &buf, 1)) ){
    if ( i==-1 || write(*dest, &buf, 1)==-1 ) 
      return 1;
  }
  return 0;
}

