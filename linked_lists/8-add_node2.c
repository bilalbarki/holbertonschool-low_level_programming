#include <stdlib.h>
#include "list.h"
int length(char *str);
void copy_string(char *dest, char *source);

/* allocates a new node at the end
   and links it*/
int add_node(List **list, char *str){
  List *node, *i;
  node = malloc( sizeof(List) );
  if (node==NULL) 
    return 1;
  node->str=malloc( sizeof(char)*(length(str)+1) );
  if (node->str==NULL){
    free(node);
    return 1;
  }
  copy_string(node->str,str);
  node->next=NULL;
  if (*list==NULL){
    *list=node;
  }
  else{
    for(i=*list ; i->next ; i=i->next);
    i->next=node;
  }
  return 0;
}

/*counts length*/
int length(char *str){
  int count;
  for(count=0;str[count];count++);
  return count;
}

/*copies string*/
void copy_string(char *dest, char *source){
  int i;
  for (i=0;source[i];i++)
    dest[i]=source[i];
  dest[i]='\0';
}
