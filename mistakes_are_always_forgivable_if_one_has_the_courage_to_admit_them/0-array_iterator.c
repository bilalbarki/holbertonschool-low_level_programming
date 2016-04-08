void array_iterator(int *a, int size, void (*p)(int)){
  int i;
  for (i=0;i<size;i++){
    (*p)(a[i]);
  }
}
