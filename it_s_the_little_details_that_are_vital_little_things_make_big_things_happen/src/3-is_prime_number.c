/*checks if a number is prime*/

int isPrime(int,int);

int is_prime_number(int n){
  if (n<2)
    return 0;
  return isPrime(n,n/2);
}

int isPrime(int num,int i){
  if(i==1){
    return 1;
  }
  else{
    if(num%i==0)
      return 0;
    else
      return isPrime(num,i-1);
  }
}
