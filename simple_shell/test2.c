#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
int string_ncompare(const char *s, const char *t, size_t n);
void print_tab(char **split);
char **string_split(const char *str, char separator);
/*

int search_dir(char **args, char **envp){
DIR *directory;

}*/

void print_line(char *line){
  for (;*line;line++)
    print_char(*line);
}

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], char *envp[]){
  int i;
  char **paths;
  DIR *directory;
  struct dirent *dir_info;
  for (i=0;envp[i];i++){
    if ( string_ncompare(envp[i],"PATH",4) == 0 ){
      paths=string_split(envp[i]+5, ':');
      break;
    }
  }
  for (i=0;paths[i];i++){
    directory=opendir(paths[i]);
    if (directory==NULL){
      continue;
    }
    while( ( dir_info=readdir(directory) )!=NULL ){
      print_line(dir_info->d_name);
      print_line("\n");
      closedir(directory);
    }
  }
  free_tab(paths);
  return 1;
}

int string_ncompare(const char *s, const char *t, size_t n) {
  for ( ; n--; s++, t++) {
    if(*s != *t) {
      return *s - *t;
    }
  }
}
