/*replicates strncpy*/
char *string_ncopy(char *dest, const char *src, int n){
  int i;
  char *dest_start;
  dest_start=dest;
  for (i=0;i<n && *(src+i)!='\0';i++)
    *(dest++)=*(src+i);
  for (;i<n;i++)
    *(dest++)='\0';
  return dest_start;
}
