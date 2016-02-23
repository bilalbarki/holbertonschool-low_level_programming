int first_digit(int n){
  int temp;
  for (temp=0;n!=0;n=n/10)
    temp=n; /*loop will end with first digit in temp*/
  if (temp<0)
    temp=temp*(-1);
  return temp;
}
