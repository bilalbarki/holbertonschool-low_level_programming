int print_char(char c);

void print_string(char *str){ /*prints string*/
  int c;
  for(c=0;*(str+c);c++){
    print_char(*(str+c));
  }
}
