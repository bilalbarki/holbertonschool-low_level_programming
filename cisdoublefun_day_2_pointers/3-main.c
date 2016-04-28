#include <stdio.h>
#include <string.h>
char *rev_string(char *);

int main(void)
{
  char *s;

  s = strdup("Holberton");
  printf("%s\n", s);
  s = rev_string(s);
  printf("%s\n", s);

  s = strdup("Holbertons");
  printf("%s\n", s);
  s = rev_string(s);
  printf("%s\n", s);

  s = strdup("I am awesome");
  printf("%s\n", s);
  s = rev_string(s);
  printf("%s\n", s);

  s = strdup("a");
  printf("%s\n", s);
  s = rev_string(s);
  printf("%s\n", s);

  s = strdup("Hello");
  printf("%s\n", s);
  s = rev_string(s);
  printf("%s\n", s);

  s = strdup("Hello1");
  printf("%s\n", s);
  s = rev_string(s);
  printf("%s\n", s);
  return (0);
}
