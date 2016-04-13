#include <stdlib.h>

int **alloc_grid(int width, int height){
  int **array,i,j;
  if (width<0 || height<0) return NULL;
  array = malloc(height * sizeof(int *));
  if(array == NULL) return NULL;
  for(i = 0; i < height; i++){
    array[i] = malloc(width * sizeof(int));
    if(array[i] == NULL){
      i--;
      for(; i>= 0; i--) free(array[i]);
      free(array);
      return NULL;
    }
  }
  for (i=0;i<height;i++){
    for (j=0;j<width;j++){
      array[i][j]=0;
    }
  }
  return array;
}
