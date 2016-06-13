#include <unistd.h>
#include <wchar.h>
#include <stdlib.h>
char *convert(unsigned long num, int base, int capital);

int print_char(char c)
{
  return (write(1, &c, 1));
}

int print_string(char *str) {
  int count = 0;
  for (;str[count];count++) {
    print_char(str[count]);
  }
  return count;
}

int print_string_wchar_t(wchar_t *str) {
  int count = 0;
  for (;str[count];count++) {
    print_char(str[count]);
  }
  return count;
}

int print_string_printable(char *str) {
  int count = 0;
  char *ptr;
  for (;str[count];count++) {
    if (str[count]<32 || str[count]>=127){
      print_char('\\');
      ptr = convert(str[count], 16, 1);
      if (ptr[1]=='\0'){
	print_char('0');
      }
      print_string(ptr);
      free(ptr);
    }
    else {
      print_char(str[count]);
    }
  }
  return count;
}
