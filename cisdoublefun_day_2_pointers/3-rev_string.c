/*reverses a string*/

char *rev_string(char *str){
  int i,j;
  for (i=0;str[i];i++);
  i--;
  for (j=0;j<=i/2;j++){
    char temp;
    temp=str[i-j];
    str[i-j]=str[j];
    str[j]=temp;
  }
  return str;
}
