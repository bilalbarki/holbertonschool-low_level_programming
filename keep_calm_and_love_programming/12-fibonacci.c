#include <stdio.h>
void addPrevPrevPrev(void);
void prevPrevEqualPrev(void);
void prevEqualNumber(void);
void printNumber(void);

/*global variables*/
char prevprev[22]={0};
char prev[22]={0};
char number[22]={0};

int main(){
  int i;
  prev[21]=1;
  for (i=1;i<99;i++){
    addPrevPrevPrev(); /*number=prevprev+prev*/
    printNumber(); /*print the array number*/
    if (i!=98) /*add , & ' ' except for last*/
      printf(", ");
    prevPrevEqualPrev(); /*prevprev=prev*/
    prevEqualNumber(); /*prev=number*/
  }
  printf("\n");
  return 0;
}

/*function for prevprev=prev*/
void prevPrevEqualPrev(void){
  int i;
  for(i = 21; i > -1; i--)
    prevprev[i]=prev[i];

}

/*function for prev=number*/
void prevEqualNumber(void){
  int i;
  for(i = 21; i > -1; i--)
    prev[i]=number[i];
}

/*function for number=prevprev+prev*/
void addPrevPrevPrev(void)
{
  int carry, i;
  carry=0; /*carry initial value 0*/
  for(i = 21; i > -1; i--){
    if ( (carry + (int)prevprev[i] + (int)prev[i] ) <10 )
      {
	number[i] = (char) (carry + (int)prevprev[i] + (int)prev[i]);
	carry=0;
      }

    else
      {
	number[i] = (char) ((carry + (int)prevprev[i] + (int)prev[i])%10);
	carry=1;
      }
  }
  if(carry>0){
    number[i+1]=carry;
  }
}
/*Function for printing number*/
void printNumber(void){
  int i, flag;
  flag=0;
  for(i = 0; i < 22; i++){
    if (number[i]>0)
      flag=1;
    if (flag==1)
      printf("%u",number[i]);
  }
}
