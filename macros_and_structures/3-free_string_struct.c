#include <stdlib.h>
#include "str_struct.h"

/*frees allocated space for struct String*/
void free_string_struct(struct String *str){
  free(str->str);
  free(str);
}
