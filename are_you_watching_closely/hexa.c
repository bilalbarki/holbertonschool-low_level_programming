#include <stdarg.h>
#include <stdlib.h>
#include "my_functions.h"

/*hexa print*/
void hexa_print(va_list *list, int *count, short h, short l, short capital) {
  if (l==0 && h==0){
    unsigned int num= va_arg(*list,unsigned int);
    if (num > 0)
      hexa_noflag(num, count, capital);
    else{
      print_char('-');
      *count+=1;
      hexa_noflag(((unsigned long)(num+1)*(-1))+1, count, capital);
    }
  }
  else if (h==0) {
    unsigned short int num= (unsigned short int)va_arg(*list,int);
    if (num > 0)
      hexa_noflag(num, count, capital);
    else{
      print_char('-');
      *count+=1;
      hexa_noflag(((unsigned long)(num+1)*(-1))+1, count, capital);
    }
  }
  
  else if (l==0) {
    unsigned long int num = va_arg(*list,unsigned long int);
    if (num > 0)
      hexa_noflag(num, count, capital);
    else{
      print_char('-');
      *count+=1;
      hexa_noflag(((unsigned long)(num+1)*(-1))+1, count, capital);
    }
  }
}

void hexa_noflag(unsigned long num, int *count, short capital){
  char *ptr;
  if (capital)
    ptr = convert(num, 16, 1);
  else
    ptr = convert(num, 16, 0);
  *count += print_string(ptr);
  free(ptr);
}
