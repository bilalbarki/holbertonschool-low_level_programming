#include <stdio.h>
#include <stdlib.h>
char **string_to_words(char *s);
void print_array_of_strings(char **a);

int main(void)
{
  char **w;

  w = string_to_words("Believing in negative thoughts is the single greatest obstruction to success.\n#cisfun!");
  if (w == NULL)
    {
      printf("Function failed\n");
      return (1);
    }
  print_array_of_strings(w);
  return (0);
}
