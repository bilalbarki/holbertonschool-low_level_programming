/*compares two strings*/
int shell_comp(char *s1, char *s2)
{
  if (*s2=='*' && *(s2 + 1) == '\0') return 1;
  else if (*s2 == '\0' && *s1 == '\0') return 1;
  else if (*s1 != *s2 && *s2 != '*') return 0;
  else if (*s2 == '*' && *(s2 + 1) == '*') return shell_comp(s1, s2 + 1);
  else if (*s1 == *s2) return (shell_comp(s1 + 1, s2 + 1));
  else if (*s2 == '*' && *s1 != *(s2 + 1)) return shell_comp(s1 + 1, s2);
  else if (*s2 == '*' && *s1 == *(s2 + 1)) return (shell_comp(s1, s2 + 1)
						     ||shell_comp(s1 + 1, s2));
  else return -1;
}
