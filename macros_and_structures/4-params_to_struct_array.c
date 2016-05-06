#include <stdlib.h>
#include "param_struct.h"
char **string_split(char *string);
int word_count(char *);
int length(char *);
void copy_string(struct Param *str_object, char *str);

/*stores the program’s parameters in an array of structures 
  and returns the address*/
struct Param *params_to_struct_array(int ac, char **av){
  int i;
  struct Param *param;
  param=malloc( sizeof(struct Param) * (ac + 1) );
  if (param==NULL) return NULL;
  for (i=0;i<ac;i++){
    param[i].str=av[i];
    param[i].length=length(av[i]);
    param[i].copy=malloc( sizeof(char) * (param[i].length+1) );
    if (param[i].copy==NULL){
      return NULL;
    }
    copy_string(param+i,av[i]);
    param[i].tab=string_split(av[i]);
    }
    param[ac].str=NULL;
    return param;
}


/*splits each word of a string and stores 
  them in a array of strings*/
char **string_split(char *string){
  int i,j,w_count,temp;
  char **split;
  w_count=word_count(string);
  if (w_count==0) return NULL;
  split=malloc(sizeof(char *)*(w_count+1));
  if (split==NULL) return NULL;
  split[w_count]=NULL;
  for (i=0,w_count=0;string[i]!='\0';i++,w_count++){
    for(;string[i]==' ';i++);
    if (string[i]=='\0') break;
    temp=i;
    for(j=0;string[temp]!='\0' && string[temp]!=' ';temp++,j++);
    split[w_count]=malloc(sizeof(char)*(j+1));
    if(split[w_count] == NULL){
      for(i--; w_count>= 0; w_count--) free(split[w_count]);
      free(split);
      return NULL;
    }
    split[w_count][j]='\0';
    for(j=0;string[i]!='\0' && string[i]!=' ';i++,j++) 
      split[w_count][j]=string[i];
    if (string[i]=='\0') break;
  }
  return split;
}

/*counts words*/
int word_count(char *string){
  int i, w_count;
  for (w_count=0,i=0;string[i]!='\0';i++){
    for(;string[i]==' ';i++);
    if (string[i]=='\0') break;
    for(;string[i]!='\0' && string[i]!=' ';i++);
    w_count++;
    if (string[i]=='\0') break;
  }
  return w_count;
}

/*counts length*/
int length(char *str){
  int count;
  for(count=0;str[count];count++);
  return count;
}

/*copies string*/
void copy_string(struct Param *str_object, char *str){
  int i;
  for (i=0;str[i];i++)
    str_object->copy[i]=str[i];
  str_object->copy[i]='\0';
}
