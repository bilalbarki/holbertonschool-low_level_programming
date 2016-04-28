#include <stdio.h>
void print_array(int *);
void sort_array(int *, int);

int main(void)
{
  int a[11] = {0, 3, 8, 2, 1, 1024, 98, 402, -1337, -1, 10};

  print_array(a);
  sort_array(a, 11);
  print_array(a);
  return (0);
}

void print_array(int *arr){
  int x;
  for (x=0;x<11;x++)
    printf("%d, ", arr[x]);
  printf("\n");
}
