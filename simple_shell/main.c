#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], char *envp[]){
  char **envp_c, *line, **args, **semicolon, **d_ampersand, **d_or;
  int status, last_status, i, j, k;
  last_status=1; /*stores last status*/
  envp_c=copy_envp(envp); /*copy env variables*/
  do{
    print_char('$');
    print_char(' ');
    line=read_line(0); /*read line*/
    semicolon=string_split(line, ';');
    free(line);
    for (i=0;semicolon[i];i++){ /*separate semicolon statements*/
      d_ampersand=string_split(semicolon[i], '&'); /*separate && statements*/
      for (status=0, j=0;d_ampersand[j];j++){
        if (status==0){
          d_or=string_split(d_ampersand[j], '|'); /*separate || statements*/
          for (status=1, k=0;d_or[k];k++){
	    if (status!=0){
	      args=string_split(d_or[k], ' ');
	      status=shell_execute(args, &envp_c,d_or,
				   d_ampersand, semicolon, last_status);
	      last_status=status;
	      free_tab(args);
	    }
          }
          free_tab(d_or);
        }
      }
      free_tab(d_ampersand);
    }
    free_tab(semicolon);
  } while (1);
  free_tab(envp_c);
  return 1;
}

int call_execve(char *name, char **args, char **envp, char **d_or, char **d_ampersand, char **semicolon, int i){
  pid_t pid;
  int status;
  pid=fork();
  if (pid==0){
    execve(name, args, envp);
    perror(args[0]);
    if (i) free(name);
    free_tab(args);
    free_tab(envp);
    free_tab(d_ampersand);
    free_tab(d_or);
    free_tab(semicolon);
    exit(1);
  }
  else if (pid<0){
    perror("fork");
  }
 
  do {
    waitpid(pid, &status, WUNTRACED);
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  if ( WIFEXITED(status) ) {
    status=WEXITSTATUS(status);
  }
  return status;
}

int shell_fork_and_run(char **args, char **envp, char **d_or, char **d_ampersand, char **semicolon){
  /*pid_t pid, wpid;*/
  int status, fd;
  char *envp_path;
  status=1;
  envp_path=NULL;
  if (get_index(args[0],'/')==NULL){
    if ( (envp_path = search_dir(args, envp)) ){
      status=call_execve(envp_path, args, envp, d_or, d_ampersand, semicolon, 1);
    }
    else{
      print_line(args[0]);
      print_line(": command not found");
      print_char('\n');
    }
  }
  else{
    if ( ( fd = open(args[0], O_RDONLY) ) > 0 ){
      close(fd);
      status=call_execve(args[0], args, envp, d_or, d_ampersand, semicolon, 0);
    } 
    else {
      perror(args[0]);
    }
  }
  free(envp_path);
  return status;
}
