int print_char(char c);

/*prints string*/
void print_string(char *str) {
  for (;*str;str++) print_char(*str);
}
