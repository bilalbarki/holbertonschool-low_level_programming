#include <stdio.h>

void triangles_in_the_term(int h, int n){
  int i, j, l;
  while(n!=0){ /*outer loop for n times*/
    l=h;
    for (i=1;i<=h;i++){ /*vertical*/
      for (j=h-1;j>=i;j--) /*horizontal ' '*/
	printf (" ");
      for (j=h;j<=l;j++) /*horizontal '*'*/
	printf ("*");
      printf("\n");
      l=l+2;
    }
    n--;
  }
}
