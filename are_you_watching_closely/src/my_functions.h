#include <wchar.h>
#include <stdarg.h>
char *convert(unsigned long num, int base, int capital);
void d_noflag(unsigned long num, int *count);
void d_l(long int num, int *count);
void d_ll(long int num, int *count);
void d_hh(signed char num, int *count);
void d_h(short int num, int *count);
char *checkflags(short *l, short *ll, short *h, short *hh, char *traverse);
void hexa_noflag(unsigned long num, int *count, short capital);
void hexa_print(va_list *list, int *count, short h, short l, short capital);
void o_print(va_list *list, int *count, short h, short l);
void o_noflag(unsigned long num, int *count);
int print_char(char c);
int print_string(char *str);
int print_string_wchar_t(wchar_t *str);
int print_string_printable(char *str);
void u_noflag(unsigned long num, int *count);
void u_h(unsigned short int num, int *count);
void u_l(unsigned long int num, int *count);
void u_print(va_list *list, int *count, short h, short l);
char *print_variables(va_list *list, char *traverse, int *count);
char *print_until_special(char *traverse, int *count);
void d_print(va_list *list, int *count, short l, short ll, short h, short hh);
