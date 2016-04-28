/*returns the length of a string*/

int str_len(char *str){
  int len;
  for ( len=0 ; *str ; str++ ) len++;
  return len;
}
