#include <stdlib.h>

char *convert(unsigned long num, int base, int capital) 
{ 
  char Representation[17]= "0123456789ABCDEF";
  unsigned int temp = num;
  int count = 0;
  char *ptr;
  if (!capital) {
    Representation[10]='a';
    Representation[11]='b';
    Representation[12]='c';
    Representation[13]='d';
    Representation[14]='e';
    Representation[15]='f';
  }

  do{
    temp/=base;
    count+=1;
  } while (temp!=0);
  
  ptr = malloc ( sizeof(char) * (count+1) );
  ptr[count] = '\0';
  count--;
  do 
  { 
    ptr[count] = Representation[num%base];
    count--;
    num /= base; 
   }while(num != 0); 
  return(ptr); 
}
