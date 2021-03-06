#include <stdlib.h>

/*concatenates two strings
 *s1, followed by the first n bytes of s2, and null terminated
 */
char *string_nconcat(char *s1, char *s2, int n){
  int i,j,p;
  char *concat;
  for ( i=0; s1[i]!='\0'; i++ );
  for ( j=0; s2[j]!='\0'; j++ );
  j=j+i;
  n=n+i-1;
  concat=malloc( sizeof(char) * (j+1) );
  if (concat == NULL)
    return NULL;
  for ( p=0; p<i; p++ ) concat[p]=s1[p];
  for ( i=0 ; p<=n && p<=j ; p++, i++ ) concat[p]=s2[i];
  if (n<j){
    concat[p]='\0';
  }
  return concat;
}
