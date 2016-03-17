int print_char(char c);
/*prints backslash in diagonal*/
void print_diagonal(int n){
  int j,i;
  if (n<1){
    print_char('\n');
    return;
  }
  for (i=0;i<n;i++){
    for (j=i;j>0;j--)
      print_char(' ');
    print_char('\\');
    print_char('\n');
  }
}
