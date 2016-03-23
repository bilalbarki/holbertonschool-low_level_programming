/*converts each character to uppercase*/
char *uppercase_string(char *p){
  char *x;
  for (x=p;*x!='\0'; x++){
    if (*x>='a' && *x<='z'){
      *x=*x-32;
    }
  }
  return p;
}
