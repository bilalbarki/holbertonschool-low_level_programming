/*calculates factorial*/

int factorial(int n){
  int temp;
  if (n>12) return -1;
  if (n>=1) temp=n*factorial(n-1);
  else if (n==0) return 1;
  else return -1;
  if (temp<0) return -1;
  else return temp;
}
