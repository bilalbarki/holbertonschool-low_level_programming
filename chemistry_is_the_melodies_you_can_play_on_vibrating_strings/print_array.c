int print_char(char c);
void print_number(int n);
void print_array(int *a, int n);

#include <unistd.h>

int print_char(char c)
{
  return (write(1, &c, 1));
}

/*Prints array using print_char*/
void print_array(int *a, int n){
  int i;
  i=0;
  for (;i<n;i++){
    print_number(*(a+i));
    if (i<(n-1)){
      print_char(',');
      print_char(' ');
    }
  }
  print_char('\n');
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
