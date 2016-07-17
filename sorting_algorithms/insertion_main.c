void insertion_sort(int *, int);
void print_array(int *, int);

int main(void)
{
  int array[] = {402, 94111, 98, 12, 1024, 2, 1};

  print_array(array, 7);
  insertion_sort(array, 7);
  print_array(array, 7);
  return (0);
}
