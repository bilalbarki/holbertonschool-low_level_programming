int print_char(char c);

/*returns O if a number is odd 
  'E' if even*/

char odd(int n){
  if ( (n&1) == 1) return 'O';
  else return 'E';
}
