#include <stdlib.h>

/*concatenates two strings*/
char *string_concat(char *s1, char *s2){
  int i,j,p;
  char *concat;
  for ( i=0; s1[i]!='\0'; i++ );
  for ( j=0; s2[j]!='\0'; j++ );
  j=j+i;
  concat=malloc( sizeof(char) * (j+1) );
  if (concat == NULL)
    return NULL;
  for ( p=0; p<i; p++ ) concat[p]=s1[p];
  for (i=0 ; p<=j; p++, i++ ) concat[p]=s2[i];
  return concat;
}
