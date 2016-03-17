int print_char(char c);
/*prints n number of _*/
void print_line(int n){
  if (n>0){
    for (;n>0;n--)
      print_char('_');
  }
  print_char('\n');
}
