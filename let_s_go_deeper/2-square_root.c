/*calculates natural square root*/

int calculate(int n, int m);

int square_root(int n){
  if (n == 1) return 1;
  else if (n == 0) return 0;
  else if (n < 0) return -1;
  return calculate(n, n - 1);
}

int calculate(int n, int m){
  if (m * m == n) return m;
  else if (m < 1) return -1;
  return calculate(n, m - 1);
}
