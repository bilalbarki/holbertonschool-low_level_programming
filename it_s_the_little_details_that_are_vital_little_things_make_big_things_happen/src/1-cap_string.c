/*capitalizes first character */
char *cap_string(char *p){
  char *x;
  for (x=p;*x!='\0'; x++){
    if (*x>='a' && *x<='z'){
      *x=*x-32;
      for (;*x>' ';x++);
    }
    else
      for (;*x>' ';x++)
	if (*x=='\0')
	  return p;
  }
  return p;
}
