int print_char(char c);
/*prints one char out of 2*/
void print_string_2(char *str){
  int i;
  for (i=0;*(str+i);i++){
    if (i%2==0)
      print_char(*(str + i));
  }
}
