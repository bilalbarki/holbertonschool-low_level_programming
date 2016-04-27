int print_char(char c);

/*prints all the numbers of 
  base 16, from 0 to F.*/

void print_base16(void){
  char a;
  for(a='0';a<='9';a++)
    print_char(a);
  for(a='A';a<='F';a++)
    print_char(a);
}
