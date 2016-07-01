#include "my_functions.h"

char *checkflags(short *l, short *ll, short *h, short *hh, char *traverse){
  if (*traverse == 'l'){
    if (*(traverse+1) == 'l') {
      *ll=1;
      traverse+=2;
      return traverse;
    }
    *l=1;
    traverse+=1;
  }
  
  else if (*traverse == 'h'){
    if (*(traverse+1) == 'h') {
      *hh=1;
      traverse+=2;
      return traverse;
    }
    *h=1;
    traverse+=1;
  }
  return traverse;
}
