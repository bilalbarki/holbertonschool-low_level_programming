#include <stdlib.h>
int print_char(char c);
void print_number(int n);

int (*get_op_func(char c))(int, int);

int main(int ac, char **av){
  if (ac==4 && get_op_func(*av[2])!=(NULL)){
    print_number( (*get_op_func(*av[2]))(atoi(av[1]), atoi(av[3])) );
    print_char('\n');
    return 0;
  }
  return 1;
}

#include <unistd.h>

int print_char(char c)
{
  return (write(1, &c, 1));
}

void print_number(int n)
{
  int count,i,temp,j,x;
  temp=0; /*to store prev result*/
  i=n;
  for (count=0;i!=0;count++) /*count digits*/
    i=i/10;
  if (n<0)    /*if neg print '-'*/
    print_char('-');
  do{   /*do loop to work for 0*/
    i=n;
    x=count;
    for(;x>1;x--){  /*start from beginning*/
      i=i/10;
    }
    j=i-(temp*10);  /*subtract prev value*/
    temp=i;        /*save prev value*/
    if (j<0){  /*if neg digit make pos*/
      j=j*(-1);
    }
    print_char(j+48); /*+48 for ascii*/
    count--;
  }
  while(count>0);
}
