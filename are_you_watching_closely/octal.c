#include <stdarg.h>
#include <stdlib.h>
char *convert(unsigned long num, int base, int capital);
int print_string(char *str);
int print_char(char c);
void o_noflag(unsigned long num, int *count);

void o_print(va_list *list, int *count, short h, short l){
  if (l==0 && h==0){
    unsigned int num= va_arg(*list,unsigned int);
    if (num > 0)
      o_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      o_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
  else if (h==0) {
    unsigned short int num= (unsigned short int)va_arg(*list,int);
    if (num > 0)
      o_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      o_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
  else if (l==0) {
    unsigned long int num = va_arg(*list,unsigned long int);
    if (num > 0)
      o_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      o_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }

}

void o_noflag(unsigned long num, int *count){
  char *ptr;
  ptr = convert(num, 8, 1);
  *count += print_string(ptr);
  free(ptr);
}
