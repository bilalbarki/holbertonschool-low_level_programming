#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>

int print_char(char c);
void print_tab(char **split);
void free_tab(char **split);
char *read_line(const int fd);
char **string_split(const char *str, char separator);
int shell_execute(char **, char ***);
int shell_fork_and_run(char **, char **);
char *search_dir(char **args, char **envp);
char *get_index(char *source, char character);
char **copy_envp(char *envp[], char *add_new);
int write_to_str(char *source, char *dest, char term);
int string_length(char *str);
int write_to_index(char *source, char *dest, char term, char index);

#define SUCESSFUL 0
#define FAILURE 1

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], char *envp[]){
  char **envp_c;
  envp_c=copy_envp(envp, NULL);
  char *line;
  char **args;
  int status;
  while(1){
    print_char('$');
    print_char(' ');
    line=read_line(0);
    args=string_split(line, ' ');
    free(line);
    status=shell_execute(args, &envp_c);
    free_tab(args);
  }
  return 0;
}

void print_line(char *line){
  for (;*line;line++)
    print_char(*line);
  print_char('\n');
}

int shell_fork_and_run(char **args, char **envp){
  pid_t pid, wpid;
  int status, fd;
  char *envp_path=NULL;
  pid=fork();
  if (pid==0){
    if (get_index(args[0],'/')==NULL){
      if ( envp_path = search_dir(args, envp) ){
        execve(envp_path, args, envp);
        /*free_tab(envp);*/
      }
    }
    else{
      if ( ( fd = open(args[0], O_RDONLY) ) > 0 ){
        close(fd);
        execve(args[0], args, envp);
        /*free_tab(envp);*/
      } else {
        perror("open error");
      }
    }
    /*execve(args[0], args, envp);
    if ( envp_path = search_dir(args, envp) )
      execve(envp_path, args, envp);*/
    perror(args[0]);
    free(envp_path);
    /*envp_path=NULL;*/
    free_tab(args);
    free_tab(envp);
    exit(FAILURE);
  }
  else if (pid < 0){
    perror("");
  }
  do {
    wpid = waitpid(pid, &status, WUNTRACED);
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  if ( WIFEXITED(status) ) {
    printf("Exit status was %d\n", WEXITSTATUS(status));
  }
  free(envp_path);
  return 1;
}

char *get_index(char *source, char character){
  for(;*source;source++){
    if (*source==character) return source;
  }
  return NULL;
}

char **copy_envp(char *envp[], char *add_new){
  char **copy_e;
  int i, length;
  for (i=0;envp[i];i++);
  if (add_new==NULL){
    copy_e=malloc( sizeof(char *) * (i+1) );
    copy_e[i]=NULL;
  }
  else{
    copy_e=malloc( sizeof(char *) * (i+2) );
    copy_e[i+1]=NULL;
    length=string_length(add_new);
    copy_e[i]=malloc(sizeof(char)*(length+1));
    write_to_str(add_new,copy_e[i], '\0');
  }
  for (i=0;envp[i];i++){
    length=string_length(envp[i]);
    copy_e[i]=malloc(sizeof(char)*(length+1));
    write_to_str(envp[i],copy_e[i], '\0');
  }
  return copy_e;
}

int write_to_str(char *source, char *dest, char term){
  int i;
  for(i=0;source[i];i++){
    dest[i]=source[i];
  }
  dest[i]=term;
  return i;
}

int write_to_index(char *source, char *dest, char term, char index){
  int i, count;
  for(i=index,count=0;source[count];i++, count++){
    dest[i]=source[count];
  }
  dest[i]=term;
  return i;
}
