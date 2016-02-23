int first_digit(int n){
  int temp;
  for (temp=0;n!=0;n=n/10){
    temp=n;
  }
  if (temp<0)
    temp=temp*(-1);
  return temp;
}
