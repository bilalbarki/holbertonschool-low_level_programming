/*quick sort*/
void quick_sort(int *array, int size) {
  int i, j, p, t;
  if (size < 2)
    return;
  p = array[size / 2];
  for (i = 0, j = size - 1;; i++, j--) {
    while (array[i] < p)
      i++;
    while (p < array[j])
      j--;
    if (i >= j)
      break;
    t = array[i];
    array[i] = array[j];
    array[j] = t;
  }
  quick_sort(array, i);
  quick_sort(array + i, size - i);
}
