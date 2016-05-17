#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "functions.h"

/*copy env variables*/
char **copy_envp(char *envp[]){
  char **copy_e;
  int i, length;
  for (i=0;envp[i];i++);
  copy_e=malloc( sizeof(char *) * (i+1) );
  copy_e[i]=NULL;
  for (i=0;envp[i];i++){
    length=string_length(envp[i]);
    copy_e[i]=malloc(sizeof(char)*(length+1));
    write_to_str(envp[i],copy_e[i], '\0');
  }
  return copy_e;
}

/*add to env variables*/
char **add_envp(char *envp[], char *add_new){
  char **copy_e;
  int i, length;
  for (i=0;envp[i];i++);
  copy_e=malloc( sizeof(char *) * (i+2) );
  copy_e[i+1]=NULL;
  length=string_length(add_new);
  copy_e[i]=malloc(sizeof(char)*(length+1));
  write_to_str(add_new,copy_e[i], '\0');
  for (i=0;envp[i];i++){
    length=string_length(envp[i]);
    copy_e[i]=malloc(sizeof(char)*(length+1));
    write_to_str(envp[i],copy_e[i], '\0');
  }
  free_tab(envp);
  return copy_e;
}

/*remove from env variables*/
char **remove_envp(char *envp[], char *remove_ptr){
  char **copy_e;
  int i, j, length;
  for (i=0;envp[i];i++);
  copy_e=malloc( sizeof(char *) * (i) );
  copy_e[i-1]=NULL;
  for (i=0, j=0;envp[i];i++){
    if (envp[i]!=remove_ptr){
      length=string_length(envp[i]);
      copy_e[j]=malloc(sizeof(char)*(length+1));
      write_to_str(envp[i],copy_e[j], '\0');
      j++;
    }
  }
  free_tab(envp);
  return copy_e;
}

/*get environment variable*/
char *get_env(char *name, char **envp){
  int i, length;
  length=string_length(name);
  for (i=0;envp[i];i++){
    if ( string_ncompare(envp[i],name,length) == 0 ){
      return envp[i];
    }
  }
  return NULL;
}

/*get env variable index*/
int get_env_index(char *name, char **envp){
  int i, length;
  length=string_length(name);
  for (i=0;envp[i];i++){
    if ( string_ncompare(envp[i],name,length) == 0 ){
      return i;
    }
  }
  return -1;
}

/*char **copy_envp(char *envp[], char *add_ptr, char *remove_ptr){
  char **copy_e;
  int i, j, length;
  for (i=0;envp[i];i++);
  if (add_ptr){
    copy_e=malloc( sizeof(char *) * (i+2) );
    copy_e[i+1]=NULL;
    length=string_length(envp[i]);
    copy_e[i]=malloc(sizeof(char)*(length+1));
    write_to_str(envp[i],copy_e[i], '\0');
  }
  else if (remove_ptr){
    copy_e=malloc( sizeof(char *) * (i) );
    copy_e[i-1]=NULL;
    for (i=0, j=0;envp[i];i++){
      if (envp[i]!=remove_ptr){
        length=string_length(envp[i]);
        copy_e[j]=malloc(sizeof(char)*(length+1));
        write_to_str(envp[i],copy_e[j], '\0');
        j++;
      }
    }
    return copy_e;
  }
  else{
    copy_e=malloc( sizeof(char *) * (i+1) );
    copy_e[i]=NULL;
  }
  for (i=0;envp[i];i++){
    length=string_length(envp[i]);
    copy_e[i]=malloc(sizeof(char)*(length+1));
    write_to_str(envp[i],copy_e[i], '\0');
  }
  return copy_e;
  }*/
