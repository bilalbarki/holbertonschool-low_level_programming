#include <stdio.h>

int main(void)
{
  int i;
  for (i=1;i<101;i++) /*1to100*/
    {
      if (i%3==0 && i%5==0){ /*multiple of 3and5*/
        printf("FizzBuzz");
      }
      else if (i%3==0){ /*multiple of 3*/
        printf("Fizz");
      }
      else if (i%5==0){ /*multiple of 5*/
        printf("Buzz");
      }
      else{
        printf("%d", i);
      }
      if (i!=100) /*space*/
        {
          printf(" ");
        }
    }
  return (0);
}
