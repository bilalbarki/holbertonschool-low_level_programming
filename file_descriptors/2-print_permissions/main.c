#include <unistd.h>
#include <sys/stat.h>

int print_char(char c);
void convert(char *dest, struct stat *fileStat);
void print_string(char *str);

int main(int argc, char *argv[]){
  struct stat permissions;
  char x[11];
  if (argc!=2) return 1;
  if ( stat(argv[1], &permissions) < 0 ) return 1;
  convert(x,&permissions);
  print_string(x);
  print_char('\n');
  return 0;
}

void convert(char *dest, struct stat *fileStat){
  dest[0]= (S_ISDIR(fileStat->st_mode)) ? 'd' : '-';
  dest[1]= (fileStat->st_mode & S_IRUSR) ? 'r' : '-';
  dest[2]= (fileStat->st_mode & S_IWUSR) ? 'w' : '-';
  dest[3]= (fileStat->st_mode & S_IXUSR) ? 'x' : '-';
  dest[4]= (fileStat->st_mode & S_IRGRP) ? 'r' : '-';
  dest[5]= (fileStat->st_mode & S_IWGRP) ? 'w' : '-';
  dest[6]= (fileStat->st_mode & S_IXGRP) ? 'x' : '-';
  dest[7]= (fileStat->st_mode & S_IROTH) ? 'r' : '-';
  dest[8]= (fileStat->st_mode & S_IWOTH) ? 'w' : '-';
  dest[9]= (fileStat->st_mode & S_IXOTH) ? 'x' : '-';
  dest[10]='\0';
}

void print_string(char *str){
  for(;*str;str++) print_char(*str);
}
