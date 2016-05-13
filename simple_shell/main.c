#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
void print_string(char *str);
void print_tab(char **split);
void free_tab(char **split);
void get_split_exec_loop();
char *read_line(const int fd);
char **string_split(const char *str, char separator);
int shell_fork_and_run(char **);

#define SUCESSFUL 0
#define FAILURE 1

int main (int argc, char *argv[], char *envp[]){
  char x;
  x='n';
  while(x!='y'){
    print_string("Do you admit :D??? (y/n) ");
    scanf("%c",&x);
    print_char('\n');
  }
  get_split_exec_loop();
  return SUCESSFUL;
}

void print_line(char *line){
  for (;*line;line++)
    print_char(*line);
}

void get_split_exec_loop(){
  char *line;
  char **args;
  int status;
  do{
    print_char('$');
    print_char(' ');
    line=read_line(0);
    args=string_split(line, ' ');
    status=shell_fork_and_run(args);
    free(line);
    free_tab(args);
  } while(status);
}

int shell_fork_and_run(char **args){
  pid_t pid, wpid;
  int status;
  pid=fork();
  if (pid==0){
    
    if (execvp(args[0], args) == -1){
      perror("");
      exit(FAILURE);
    }
  }
  else if (pid < 0){
    perror("");
  }
  do {
    wpid = waitpid(pid, &status, WUNTRACED);
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  return 1;
}

void print_string(char *str){
  for(;*str;str++){
    print_char(*str);
  }
}
