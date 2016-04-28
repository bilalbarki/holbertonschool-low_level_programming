/*sorts arrays of integers*/

void sort_array(int *a, int n){
  int i, temp;
  for (n--;n>0;n--){
    for ( i=0; i<n; i++ ){
      if ( a[i] > a[i+1] ){
	temp=a[i];
	a[i]=a[i+1];
	a[i+1]=temp;
      }
    }
  }
}
