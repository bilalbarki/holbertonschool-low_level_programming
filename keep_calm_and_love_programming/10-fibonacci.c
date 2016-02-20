#include <stdio.h>

int main(void)
{
  int prevprev, prev, number, sum;
  sum=0;
  prevprev=0;
  prev=1;
  number=0;
  while (number<4000001){ /*repeat till 4000000*/
    number=prevprev+prev;
    prevprev=prev;
    prev=number;
    if (number%2==0){ /*if factor of 2*/
      sum=sum+number;
    }
  }
  printf("%d\n",sum);
  return 0;
}
