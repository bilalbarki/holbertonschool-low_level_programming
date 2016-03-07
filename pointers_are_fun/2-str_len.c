int str_len(char *str){ /*calculates string length*/
  int counter;
  counter=0;
  while(*(str+counter)){
    counter++;
  }
  return counter;
}
