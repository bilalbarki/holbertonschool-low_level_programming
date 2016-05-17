#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

int strings_compare(const char *s1, const char *s2){
  int i;
  for (i=0;*(s1+i)==*(s2+i);i++){
    if (*(s1+i)=='\0')
      return 0;
  }
  return (*(s1+i)-*(s2+i));
}

int convert_string_to_int(char *source_string){
  int n=0;
  for(;*source_string;source_string++){
    if ( (*source_string<'0') || (*source_string>'9') ) return 0;
    n*=10;
    n=n +( ( (int)(*source_string) ) - '0' );
    if (n>255) return 0;
  }
  return n;
}

int write_to_str(char *source, char *dest, char term){
  int i;
  for(i=0;source[i];i++){
    dest[i]=source[i];
  }
  dest[i]=term;
  return i;
}

int write_to_index(char *source, char *dest, char term, char index){
  int i, count;
  for(i=index,count=0;source[count];i++, count++){
    dest[i]=source[count];
  }
  dest[i]=term;
  return i;
}
