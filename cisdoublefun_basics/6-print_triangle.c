int print_char(char c);

/*print a triangle with n height*/

void print_triangle(int n){
  int i,j;
  for (i=0;i<=n;i++){
    for (j=0;j<i;j++){
      print_char('*');
    }
    print_char('\n');
  }

  for (i=(n-1);i>=0;i--){
    for (j=i;j>0;j--){
      print_char('*');
    }
    print_char('\n');
  }
}
