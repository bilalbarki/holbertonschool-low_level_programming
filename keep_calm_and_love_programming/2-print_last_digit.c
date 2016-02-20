void print_char(char);

void print_last_digit(int n)
{
  n=n%10; /*obtain last digit*/
  if (n<0){
    n=n*(-1); /*make pos if neg*/
  }
  print_char(n+48);
}
