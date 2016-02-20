#include <stdio.h>
void divideit();
int remainderr();
/*global variables*/
/*dividend=612852475143 and s is for looping*/
char dividend[13]={6,1,2,8,5,2,4,7,5,1,4,3,'s'};
int divisor;
char quotient[13]={0};
int temp;

int main(){
  int largest;/*to save largest prime factor*/
  largest=0;
  divisor = 2;/*start with 2*/
  /*keep looping until dividend is equal to 0*/
  while(dividend[0]!=0){
    if(remainderr()!=0)
      divisor = divisor + 1;
    else {
      divideit(); /*divident=divident/divisor*/
      if(largest<divisor)
	largest=divisor; /*store largest*/
      /*if divident=1 break loop*/
      if(dividend[0]==1 && dividend[1]=='s')
	break;
    }
  }
  printf("%d\n",largest);
  return 0;
}

void divideit() /*divident=divident/divisor*/
{
  int i, j, flag;
  flag=0;
  i=0;
  j=0;
  temp=0;
  while(dividend[i]!='s'){ /*until 's'*/
    temp=temp*10 + (int)(dividend[i]);
    if (temp<divisor){
      if (flag==1) /*make sure no 0s in start*/
	quotient[j++]=0;
    }
    else{
      flag=1;
      quotient[j++] = (char)(temp / divisor);
      temp = temp % divisor;
    }
    i++;
  }
  dividend[i]='s'; /*put s at the end*/
  quotient[j] = 's';
  for (i=0;i<13;i++) /*dividend=quotient*/
    dividend[i]=quotient[i];
}
/*follows same principle as above one*/
int remainderr()
{
  int i;
  i=0;
  temp=0;
  while(dividend[i]!='s'){
    temp=temp*10 + (int)(dividend[i]);
    if (!(temp<divisor)){
      temp = temp % divisor;
    }
    i++;
  }
  return temp;
}
