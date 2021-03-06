#include <stdlib.h>
#include "list.h"

void free_node(List *del);

/*removes and frees a node from a list at a 
  specific index*/
void remove_from_list(List **list, int index){
  int i;
  List *prev, *del;
  if (index<0) return;
  del=*list;
  for (i=0;i<index && del->next;i++){
    prev=del;
    del=del->next;
  }
  if (i==0){
    prev=*list;
    *list=(*list)->next;
    free_node(prev);
  }
  else{
    prev->next=del->next;
    free_node(del);
  }
}

/*frees a node*/
void free_node(List *del){
  free(del->str);
  free(del);
}
