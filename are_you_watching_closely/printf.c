#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_functions.h"
#include <wchar.h>
int print_string_wchar_t(wchar_t *str);

int printf(char *format, ...) {
  char *traverse; 
  int count = 0;
   
  va_list arg; 
  va_start(arg, format); 
  traverse = format;
  
  if ( *traverse ) {
    while(1) { 
      if (*traverse == '%') {
	traverse++;
	traverse = print_variables(&arg, traverse, &count);
      }
      else if (*traverse == '\0') {
	break;
      }
      traverse = print_until_special(traverse, &count);
    }
  }
  va_end(arg);
  return count;
}

char *print_variables(va_list *list, char *traverse, int *count) {
  char *ptr;
  short ll=0;
  short l=0;
  short hh=0;
  short h=0;
  traverse = checkflags(&l, &ll, &h, &hh, traverse);
  if (*traverse == 'd' || *traverse == 'i') {
    d_print(list, count, l, ll, h, hh);
    traverse++;
  }
  
  else if (*traverse == 's') {
    if (l==0) {
      ptr = va_arg(*list, char *);
      *count += print_string(ptr);
    }
    else if (l==1){
      wchar_t *i = va_arg(*list, wchar_t);
      *count += print_string_wchar_t(i);
    }
    traverse++;
  }

  else if (*traverse == 'u') {
    /*unsigned int i= va_arg(*list,unsigned int);
    ptr = convert(i, 10, 1);
    *count += print_string(ptr);
    free(ptr);*/
    u_print(list, count, h, l);
    traverse++;
  }

  else if (*traverse == 'o') {
    /*unsigned int i= va_arg(*list,unsigned int);
    ptr = convert(i, 10, 1);
    *count += print_string(ptr);
    free(ptr);*/
    o_print(list, count, h, l);
    traverse++;
  }

  else if (*traverse == 'b') {
    unsigned int i= va_arg(*list,unsigned int);
    ptr = convert(i, 2, 1);
    *count += print_string(ptr);
    free(ptr);
    traverse++;
  }

  else if (*traverse == 'S') {
    ptr = va_arg(*list, char *);
    *count += print_string_printable(ptr);
    traverse++;
  }

  else if (*traverse == 'X' || *traverse == 'x') {
    if (*traverse == 'X')
      hexa_print(list, count, l, h, 1);
    else hexa_print(list, count, l, h, 0);
    /*unsigned int i= va_arg(*list,unsigned int);
    if (*traverse == 'X') ptr = convert(i, 16, 1);
    else ptr = convert(i, 16, 0);
    *count += print_string(ptr);
    free(ptr);*/
    traverse++;
  }

  else if (*traverse == 'c') {
    unsigned int i= va_arg(*list,int);
    print_char((char)i);
    *count+=1;
    traverse++;
  }

  else if (*traverse == 'p') {
    void *i = va_arg(*list,void *);
    unsigned int *x = (unsigned int *)(&i);
    int divide = sizeof(void *)/sizeof (unsigned int);
    print_string("0x");
    for (divide--; divide >= 0 ; divide--) {
      ptr = convert(*(x+divide), 16, 0);
      print_string(ptr);
      free(ptr);
    }
    traverse++;
  }
  
  else {
    print_char('%');
    *count+=1;
  }
  
  return traverse;
} 

char *print_until_special(char *traverse, int *count) {
  while( *traverse != '%' && *traverse )
  {
      print_char(*traverse);
      *count = *count + 1;
      traverse++;
  }
  return traverse;
}
