/*converts string to int*/

int string_to_int(char *str) {
  int number = 0;
  for (; *str ; str++) {
    number *= 10;
    number += (int)(*str - 48);
  }
  return number;
}
