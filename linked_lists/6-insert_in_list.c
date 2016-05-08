#include <stdlib.h>
#include "list.h"

int len(char *str);
void c_string(char *write, char *string);

/*inserts a new node at a specific index*/
int insert_in_list(List **list, char *content, int index){
  int i;
  List *node, *left, *right;
  if (index<0) return 0;
  right=*list;
  for (i=0;i<index && right;i++){
    left=right;
    right=right->next;
  }
  node=malloc( sizeof(List) );
  node->str=malloc( sizeof(char)*(len(content)+1) );
  c_string(node->str,content);
  if (i==0){
    node->next=*list;
    *list=node;
  } else{
    left->next=node;
    node->next=right;
  }
  return 0;
}

/*counts length*/
int len(char *str){
  int count;
  for(count=0;str[count];count++);
  return count;
}

/*copies string*/
void c_string(char *write, char *string){
  int i;
  for (i=0;string[i];i++)
    write[i]=string[i];
  write[i]='\0';
}
