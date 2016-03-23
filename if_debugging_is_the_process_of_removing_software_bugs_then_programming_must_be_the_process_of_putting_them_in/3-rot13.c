char *rot13(char *p){
  char *x;
  for (x=p;*x!='\0'; x++){
    if ( ( *x>='a' && *x<='m' ) || ( *x>='A' && *x<='M' ) )
      *x=*x+13;
    else if ( ( *x>='n' && *x<='z' ) || ( *x>='N' && *x<='Z' ) )
      *x=*x-13;
  }
  return p;
}
