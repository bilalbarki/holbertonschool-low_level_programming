int string_to_int(char *str);
int print_char(char c);

/*prints an X, if odd then at the center the character X is printed */
int main(int argc, char *argv[]) {  
  int i, count = 0, max, odd;
  if (argc == 1) return 1;
  max = string_to_int(argv[1]);
  odd = max % 2;
  for (i=0; i<max; i++){
    int j;
    for (j=0; j<max; j++) {
      if (j == count) {
	if ( odd && ( i == (max/2) ) )
	  print_char('X');
	else
	  print_char('\\');
      }
      else if (j == (max - count - 1))
	print_char('/');
      else
	print_char(' ');
    }
    count++;
    print_char('\n');
  }
  return 0;
}
