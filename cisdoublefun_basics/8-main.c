int print_char(char c);
void print_number(int n);

int main(void)
{
  print_number(98);
  print_char('\n');
  print_number(402);
  print_char('\n');
  print_number(1024);
  print_char('\n');
  print_number(0);
  print_char('\n');
  print_number(-98);
  print_char('\n');

  print_number(-2147483648);
  print_char('\n');
  print_number(2147483647);
  print_char('\n');
  return (0);
}
