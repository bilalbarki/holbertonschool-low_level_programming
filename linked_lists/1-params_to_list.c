#include <stdlib.h>
#include "list.h"

int length(char *str);
void copy_string(char *write, char *string);
int add_node(List **list, char *str);

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
void copy_string(char *write, char *string){
  int i;
  for (i=0;string[i];i++)
    write[i]=string[i];
  write[i]='\0';
}
