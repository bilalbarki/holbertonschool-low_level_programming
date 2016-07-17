#include <string.h>

/*sorts a string array*/
void sort_str_array(char **array) {
  int i, j;
  for (i=1; array[i]!=NULL ; i++) {
    for (j=1; array[j]!=NULL; j++) {
      if (strcmp( array[j-1],array[j]  ) > 0) {
	char *temp;
	temp = array[j];
	array[j] = array[j-1];
	array[j-1] = temp;
      }
    }
  } 
}
