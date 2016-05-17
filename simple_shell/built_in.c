#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

/*builtin cd*/
int shell_cd(char **args, char ***envp){
  char *path;
  if (args[1]==NULL){
    if ( (path=get_env("HOME", *envp) ) ){
      if ( chdir(path+5) !=0 ){
	print_line("cd: $HOME not defined");
	print_char('\n');
	return 1;
      }
    }
  }
  else if (args[1][0]=='-' && args[1][1]=='\0' && args[2]==NULL){
    if ( (path=get_env("OLDPWD", *envp) ) ){
      if ( chdir(path+6) !=0 ){
	print_line("cd: $OLDPWD not defined");
	print_char('\n');
	return 1;
      }
    }
  }
  else{
    if ( chdir(args[1]) !=0 ){
      perror(args[1]);
      return 1;
    }
  }
  return 0;
}

/*builtin exit*/
int shell_exit(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon){
  int status;
  if (args[1]==NULL){
    free_tab(*envp);
    free_tab(args);
    free_tab(d_or);
    free_tab(d_ampersand);
    free_tab(semicolon);
    exit(0);
  }
  else if (args[2]==NULL){
    if ( ( status=convert_string_to_int(args[1]) ) == 0){
      print_line("exit: Usage: exit [0-255]\n");
      return 1;
    }
    free_tab(*envp);
    free_tab(args);
    free_tab(d_or);
    free_tab(d_ampersand);
    free_tab(semicolon);
    exit(status);
  }
  else{
    print_line("exit: Usage: exit [0-255]\n");
  }
  return 1;
}

/*shell env*/
int shell_env(__attribute__((unused)) char **args, char ***envp){
  print_tab(*envp);
  return 0;
}

/*builtin setenv*/
int shell_setenv(char **args, char ***envp){
  char *line, **envp_new;
  int i, count;
  if (args[3]==NULL){ 
    count=string_length(args[1])+string_length(args[2]);
    if ( (i=get_env_index(args[1], *envp)) >= 0 ){
      free( (*envp)[i] );
      (*envp)[i]=malloc(sizeof(char)*(count+2));
      count=(write_to_str(args[1], (*envp)[i], '='))+1;
      write_to_index(args[2], (*envp)[i], '\0', count);
      return 0;
    }
    line=malloc(sizeof(char)*(count+2));
    i=(write_to_str(args[1], line, '='))+1;
    write_to_index(args[2], line, '\0', i);
    envp_new=add_envp(*envp, line);
    free(line);
    *envp=envp_new;
    return 0;
  }
  print_line("setenv: Usage: setenv VARIABLE VALUE");
  return 1;
}

/*builtin unsetenv*/
int shell_unsetenv(char **args, char ***envp){
  char *line, **envp_new;
  if (args[2]==NULL){ 
    if ( (line=get_env(args[1], *envp)) ){
      envp_new=remove_envp(*envp, line);
      *envp=envp_new;
      return 0;
    }
    else{
      print_line(args[1]);
      print_line(" doesn't exist");
      return 1;
    }
  }
  print_line("setenv: Usage: unsetenv VARIABLE VALUE");
  return 1;
}
