#include "param_struct.h"
#include <stdlib.h>

void free_params_structs_array(struct Param *array){
  int i,j;
  for( i=0; array[i].str!=NULL; i++){
    free(array[i].copy);
  }

  for( i=0; array[i].str!=NULL; i++){
    for (j=0;array[i].tab[j]!=NULL;j++)
      free(array[i].tab[j]);
    /*free(array[i].tab[j]);*/
    free(array[i].tab);
   }
  free(array);
}
