void reverse_string(char *s){ /*reverses string*/
  char *t; /*pointer for end*/
  char *x; /*pointer for start*/
  t=s;
  while(*t)
    t++;
  for(x=s;t>x;x++){
    char temp;
    t--;
    temp=*t;
    *t=*x;
    *x=temp;
  }
}
