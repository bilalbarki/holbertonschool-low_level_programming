/*encodes a string into 1337*/
char *leet(char *p){
  char *x;
  for (x=p;*x!='\0'; x++){
    if (*x=='a' || *x=='A')
      *x='4';
    else if ((*x=='e' || *x=='E'))
      *x='3';
    else if ((*x=='o' || *x=='O'))
      *x='0';
    else if ((*x=='t' || *x=='T'))
      *x='7';
    else if ((*x=='l' || *x=='L'))
      *x='1';
  }
  return p;
}
