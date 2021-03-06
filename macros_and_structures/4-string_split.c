#include <stdlib.h>

int word_count(char *string);

/*splits each word of a string and stores
  them in a array of strings*/
char **string_split(char *string){
  int i,j,w_count,temp;
  char **split;
  w_count=word_count(string);
  if (w_count==0) return NULL;
  split=malloc(sizeof(char *)*(w_count+1));
  if (split==NULL) return NULL;
  split[w_count]=NULL;
  for (i=0,w_count=0;string[i]!='\0';i++,w_count++){
    for(;string[i]==' ';i++);
    if (string[i]=='\0') break;
    temp=i;
    for(j=0;string[temp]!='\0' && string[temp]!=' ';temp++,j++);
    split[w_count]=malloc(sizeof(char)*(j+1));
    if(split[w_count] == NULL){
      for(w_count--; w_count>= 0; w_count--) free(split[w_count]);
      free(split);
      return NULL;
    }
    split[w_count][j]='\0';
    for(j=0;string[i]!='\0' && string[i]!=' ';i++,j++)
      split[w_count][j]=string[i];
    if (string[i]=='\0') break;
  }
  return split;
}

/*counts words*/
int word_count(char *string){
  int i, w_count;
  for (w_count=0,i=0;string[i]!='\0';i++){
    for(;string[i]==' ';i++);
    if (string[i]=='\0') break;
    for(;string[i]!='\0' && string[i]!=' ';i++);
    w_count++;
    if (string[i]=='\0') break;
  }
  return w_count;
}
