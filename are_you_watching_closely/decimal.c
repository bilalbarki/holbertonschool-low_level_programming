#include <stdarg.h>
#include <stdlib.h>
char *convert(unsigned long num, int base, int capital);
int print_string(char *str);
int print_char(char c);

void d_noflag(unsigned long num, int *count);
void d_l(long int num, int *count);
void d_ll(long int num, int *count);
void d_hh(signed char num, int *count);
void d_h(short int num, int *count);

void d_print(va_list *list, int *count, short l, short ll, short h, short hh) {
  if (ll==0 && l==0 && hh==0 && h==0){
    int num = va_arg(*list,int);
    if (num > 0)
      d_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      d_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
  else if (h) {
    short num = (short)va_arg(*list, int);
    if (num > 0)
      d_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      d_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
  else if (hh) {
    signed char num = (signed char)va_arg(*list,int);
    d_hh(num, count);
  }

  else if (ll){
    long int num = va_arg(*list,long int);
    if (num > 0)
      d_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      d_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }

  else if (l) {
    long num = va_arg(*list,long int);
    if (num > 0)
      d_noflag(num, count);
    else{
      print_char('-');
      *count+=1;
      d_noflag(((unsigned long)(num+1)*(-1))+1, count);
    }
  }
}

void d_noflag(unsigned long num, int *count) {
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}

void d_l(long int num, int *count) {
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}

void d_ll(long int num, int *count) {
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}

void d_hh(signed char num, int *count) {
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}

void d_h(short int num, int *count) {
  char *ptr;
  ptr = convert(num, 10, 1);
  *count += print_string(ptr);
  free(ptr);
}
