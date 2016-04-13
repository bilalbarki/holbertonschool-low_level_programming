#include <stdio.h>

void print_grid(int **array, int width, int height){
  int i,j;
  for (i=0;i<height;i++){
    for (j=0;j<width;j++){
      printf("%d", array[i][j]);
      printf(", ");
    }
    printf("\n");
  }
}
