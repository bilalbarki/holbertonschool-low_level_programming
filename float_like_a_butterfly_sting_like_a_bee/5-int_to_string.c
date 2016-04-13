#include <stdlib.h>

/*converts int to a string*/
char *int_to_string(int num){
  int i, temp;
  char *string;
  i=0;
  temp=num;
  if (temp==0 || temp<0) i++;
  for (; temp!=0; i++)
    temp=temp/10;
  string=malloc(sizeof(char)*(i+1));
  if (string == NULL)
    return NULL;
  string[i--]='\0';
  if (num<0) string[0]='-';
  do{
    temp=(num%10);
    if (temp<0) temp*=(-1);
    string[i]=temp+48;
    num=num/10;
    i--;
  }
  while (num!=0);
  return string;
}
