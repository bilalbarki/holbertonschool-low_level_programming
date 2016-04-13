#include <stdlib.h>
#include <stdio.h>

int **alloc_grid(int, int);
void print_grid(int **, int, int);

void free_grid(int **grid, int height){
  int i;
  for(i=0; i<height; i++){
    free(grid[i]);
  }
  free(grid);
}

int main()
{
  int **grid;

  grid = alloc_grid(5, 5);
  print_grid(grid, 5, 5);
  printf("\n");
  grid[2][3] = 98;
  grid[4][4] = 402;
  print_grid(grid, 5, 5);
  free_grid(grid, 5);
  return (0);
}

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
