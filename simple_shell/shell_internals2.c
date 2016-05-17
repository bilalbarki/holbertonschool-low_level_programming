#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

void handle_comments(char **args){
  int i,j;
  for (i=0;args[i];i++){
    if(args[i][0]=='#'){
      free(args[i]);
      for (j=i+1;args[j];j++){
	free(args[j]);
      }
      args[i]=NULL;
      break;
    }
  }
}

int shell_execute(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon, int status){
  char *builtin_str[] = {
    "cd",
    "env",
    "setenv",
    "unsetenv",
    NULL
  };
  int (*built_in[])(char **, char ***)={
    &shell_cd,
    &shell_env,
    &shell_setenv,
    &shell_unsetenv,
  };

  /*int size=sizeof(builtin_str) / sizeof(char *);*/
  int i;
  check_convert_dollar_question(args, status);
  initial_processing(args, *envp);
  /*check_convert_dollar_question(args, status);*/
  /*if (args[0]=='\0') return 0;*/
  if (args[0]==NULL) return 0;
  for (i=0;builtin_str[i];i++){
    if ( strings_compare(args[0], builtin_str[i]) == 0 ){
      return built_in[i](args, envp);
    }
  }
  if ( strings_compare(args[0], "exit") == 0 ){
    return shell_exit(args, envp, d_or, d_ampersand, semicolon);
  }
  return shell_fork_and_run(args, *envp, d_or, d_ampersand, semicolon);
}
