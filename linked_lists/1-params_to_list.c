#include <stdlib.h>
#include "list.h"

int length(char *str);
void copy_string(char *dest, char *source);
int add_node(List **list, char *str);

/*creates a new list from the command 
  line arguments*/
List *params_to_list(int ac, char **av){
  int i;
  List *list;
  list=NULL;
  for (i=ac-1;i>=0;i--){
    if (add_node(&list, av[i]) == 1)
      return NULL;
  }
  return list;
}

/* allocates a new node at the beginning
   and links it*/
int add_node(List **list, char *str){
  List *node;
  node = malloc( sizeof(List) );
  if (node==NULL)
    return 1;
  node->str=malloc( sizeof(char)*(length(str)+1) );
  if (node->str==NULL){
    free(node);
    return 1;
  }
  copy_string(node->str,str);
  node->next=*list;
  *list=node;
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
