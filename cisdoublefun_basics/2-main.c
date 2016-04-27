int print_char(char c);

int main(void)
{
  int a[5] = { 0, 1, 2, 4, 1 };
  int b[5] = { 1, 6, 2, 2, 8 };
  int i;

  i = 4;
  while (i>=0) 
    {
      print_char( ( a[i]+b[i]) +48 );
      i--;
    }
  print_char('\n');
  return (0);
}
