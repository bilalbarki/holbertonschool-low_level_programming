/*prints options, repeated not printed*/
/*--<space> means no more options ahead*/
/*--<string> -<single char>*/
#include <stdio.h>
#include <string.h>
int main(int ac, char **av){
  int i, x, comma, sflag;
  int a[255]={0};
  sflag=1;
  for( i=1, comma=0; i<ac ; i++ ){
    if (*av[i]=='-' && *(av[i]+1)=='-'){
      if ( *(av[i]+2)=='\0' ) break;
      if ( *(av[i]+3)=='\0' ){
	if (a[(int)*(av[i]+2)]==1) continue;
	a[(int)*(av[i]+2)]=1;
      }
      for( x=1; x<i ; x++ ){
	if ( !( strcmp(av[i], av[x]) ) ){
	  sflag=0;
	  break;
	}
      }
      if (comma!=0) printf(", ");
      if (sflag) printf("%s", av[i]+2);
      sflag=1;
      comma=1;
    }
    else if (*av[i]=='-' && *(av[i]+1)!='\0'){
      for (x=1;*(av[i]+x)!='\0';x++){
	if ( a[(int)*(av[i]+x)]==0 ){
	  if (comma!=0) printf(", ");
	  printf("%c", *(av[i]+x));
	  a[(int)*(av[i]+x)]=1;
	  sflag=1;
	  comma=1;
	  }
	}
     }
  }
  printf("\n");
  return 0;
}
