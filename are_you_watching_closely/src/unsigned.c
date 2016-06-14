#include <stdarg.h>
#include <stdlib.h>
#include "my_functions.h"
/*prints unsigned*/
void u_print(va_list *list, int *count, short h, short l){
  if (l==0 && h==0){
    unsigned int num= va_arg(*list,unsigned int);
    if (num > 0)
      u_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      u_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
  else if (h==0) {
    unsigned short int num= (unsigned short int)va_arg(*list,int);
    if (num > 0)
      u_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      u_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }

  else if (l==0) {
    unsigned long int num = va_arg(*list,unsigned long int);
    if (num > 0)
      u_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      u_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
}

void u_noflag(unsigned long num, int *count){
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}

void u_h(unsigned short int num, int *count){
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}

void u_l(unsigned long int num, int *count){
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}
