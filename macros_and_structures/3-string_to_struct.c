#include <stdlib.h>
#include "str_struct.h"

int length_string(char *str){
  int count;
  for (count=0;str[count];count++);
  return count;
}

void copy_string(struct String *str_object, char *str){
  int i;
  for (i=0;str[i];i++)
    str_object->str[i]=str[i];
  str_object->str[i]='\0';
}

struct String *string_to_struct(char *str){
  struct String *str_object;
  str_object=malloc( sizeof(struct String) );
  if (str_object==NULL) 
    return NULL;
  str_object->length=length_string(str);
  str_object->str=malloc( sizeof(char)*str_object->length+1 );
  if (str_object->str==NULL){ 
    /*free(str_object);*/
    return NULL;
  }
  copy_string(str_object, str);
  return str_object;
}
