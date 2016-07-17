/*bubble sort*/
void bubble_sort(int *array, int size) {
  int k, i, temp;
  for ( k=0; k<size ;k++ ) {
    for ( i=0; i < size-k-1; i++ ){
      if ( array[i] > array[i+1] ) {
	temp=array[i];
	array[i]=array[i+1];
	array[i+1]=temp;
      }
    }
  }
}
