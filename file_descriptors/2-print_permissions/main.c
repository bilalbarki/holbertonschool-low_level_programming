#include <unistd.h>
#include <sys/stat.h>

int print_char(char c);
void print_permissions(int st_mode);
void print_string(char *str);

int main(int argc, char *argv[]){
  struct stat permissions;
  if (argc!=2) return 1;
  if ( lstat(argv[1], &permissions) < 0 ) return 1;
  print_permissions(permissions.st_mode);
  print_char('\n');
  return 0;
}

void print_permissions(int st_mode){
  print_char( (S_ISDIR(st_mode)) ? 'd' : '-' );
  print_char( (st_mode & S_IRUSR) ? 'r' : '-' );
  print_char( (st_mode & S_IWUSR) ? 'w' : '-' );
  print_char( (st_mode & S_IXUSR) ? 'x' : '-' );
  print_char( (st_mode & S_IRGRP) ? 'r' : '-' );
  print_char( (st_mode & S_IWGRP) ? 'w' : '-' );
  print_char( (st_mode & S_IXGRP) ? 'x' : '-' );
  print_char( (st_mode & S_IROTH) ? 'r' : '-' );
  print_char( (st_mode & S_IWOTH) ? 'w' : '-' );
  print_char( (st_mode & S_IXOTH) ? 'x' : '-' );
}
