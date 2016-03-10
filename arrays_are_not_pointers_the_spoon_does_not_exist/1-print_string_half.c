int print_char(char c);
/*Prints second half of the string*/
void print_string_half(char *str){
  int i;
  for (i=0;*(str+i);i++);
  if (i%2==0){
    i=i/2;
    for (;*(str+i);i++)
      print_char(*(str+i));
  }
  else{
    i=(i/2)+1;
    for (;*(str+i);i++)
      print_char(*(str+i));
  }
}
