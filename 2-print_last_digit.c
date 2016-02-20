void print_char(char);

void print_last_digit(int n)
{
  n=n%10;
  if (n<0){
    n=n*(-1);
  }
  print_char(n+48);
}
