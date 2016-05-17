#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
#include "functions.h"

char *search_dir(char **args, char **envp){
  int i;
  char **paths, *dirpath;
  DIR *directory;
  struct dirent *dir_info;
  if ( (dirpath=get_env("PATH", envp)) ){
    paths=string_split(dirpath, ':');
    for (i=0;paths[i];i++){
      directory=opendir(paths[i]);
      if (directory==NULL){
	continue;
      }
      while( ( dir_info=readdir(directory) )!=NULL ){
	if ( strings_compare(dir_info->d_name,args[0])==0 ){
	  dirpath=dir_path(paths[i],dir_info->d_name);
	  free_tab(paths);
	  closedir(directory);
	  return dirpath;
	}
      }
      closedir(directory);
    }
    free_tab(paths);
  }
  return NULL;
}

char *dir_path(char *s1, char *s2){
  int i, count;
  char *joined_string;
  count=string_length(s1)+string_length(s2);
  if (count==0) return NULL;
  if (get_index(s1,'/')==NULL){
    joined_string=malloc( sizeof(char)*(count+1) );
    for (i=0; s1[i];i++)
      joined_string[i]=s1[i];
  }
  else{
    joined_string=malloc( sizeof(char)*(count+2) );
    for (i=0; s1[i];i++) 
      joined_string[i]=s1[i];
    joined_string[i]='/';
    i++;
  }
  for (count=0; s2[count];count++,i++)
    joined_string[i]=s2[count];
  joined_string[i]='\0';
  return joined_string;
}
