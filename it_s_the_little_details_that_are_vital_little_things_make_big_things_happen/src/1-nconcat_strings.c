/*replicates strncat*/
char *nconcat_strings(char *dest, const char *src, int n){
  int i;
  char *dest_start;
  dest_start=dest;
  for (;*dest!='\0';dest++);
  for (i=0;*(src+i)!='\0' && i<n;i++)
    *(dest++)=*(src+i);
  *dest='\0';
  return dest_start;
}
