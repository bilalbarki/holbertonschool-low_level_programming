void reverse_array(int *a, int n){
  int t,half,temp;
  half=n/2;
  n--;
  for(t=0;t<half;t++){
    temp=a[t];
    a[t]=a[n-t];
    a[n-t]=temp;
  }
}
