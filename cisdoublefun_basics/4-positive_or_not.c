int print_char(char c);

/*prints P if the number is pos
  N if the number is neg
  Z if the number is zero*/

void positive_or_not(int n){
  if (n>0) print_char('P');
  else if (n<0) print_char('N');
  else print_char('Z');
}
