/*checks if a string is a palindrome*/

int calculate_length(char *s);
int sherlock(char *, char *, int);

int is_palindrome(char *s){
  int length, temp;
  length=calculate_length(s);
  temp=length/2;
  return sherlock(s, s+length-1, temp);
}

int calculate_length(char *s){
  if (*s=='\0') return 0;
  return 1 + calculate_length(s+1);
}

int sherlock(char *s, char *end, int middle){
  if (middle==0) return sherlock(s+1,end-1,middle-1);
  if (*s==*end) return 1;
  else return 0;
}
