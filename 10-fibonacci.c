#include <stdio.h>

int main(void)
{
  int prevprev, prev, number, sum;
  sum=0;
  prevprev=0;
  prev=1;
  number=0;
  while (number<4000001){
    number=prevprev+prev;
    prevprev=prev;
    prev=number;
    /*printf("%d\n",number);*/
    if (number%2==0){
      sum=sum+number;
    }
  }
  printf("%d\n",sum);
  return 0;
}
