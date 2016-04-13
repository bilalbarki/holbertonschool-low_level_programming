#include <stdlib.h>

/*dynamically reserves memory and copies provided string in it*/
char *string_dup(char *x){
  int i,j;
  char *scopy;
  for ( i=0; x[i]!='\0'; i++ );
  scopy=malloc( sizeof(char) * (i+1) );
  if (scopy == NULL)
    return NULL;
  for ( j=0; j<=i; j++ ) scopy[j]=x[j];
  return scopy;
}
