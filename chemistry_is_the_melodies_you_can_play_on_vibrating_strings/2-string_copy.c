/*replicates strcpy*/
char *string_copy(char *dest, const char *src){
  int i;
  char *dest_start;
  dest_start=dest;
  for (i=0;*(src+i)!='\0';i++)
    *(dest++)=*(src+i);
  if (*(src+i)=='\0')
    *dest='\0';
  return dest_start;
}
