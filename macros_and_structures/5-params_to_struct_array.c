#include <stdlib.h>
#include "param_struct.h"

char **string_split(char *string);
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
      for(i--; i>= 0; i--) free(param[i].copy);
      free(param);
      return NULL;
    }
    copy_string(param+i,av[i]);
    param[i].tab=string_split(av[i]);
    }
    param[ac].str=NULL;
    return param;
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
