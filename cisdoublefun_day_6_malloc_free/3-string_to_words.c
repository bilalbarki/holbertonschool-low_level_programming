#include <stdlib.h>

int count(char *s){
  int i, count, flag;
  i=0;
  count=0;
  flag=1;
  while(s[i]){
    if ( !( (s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') 
	    || (s[i]>='0' && s[i]<='9') ) && flag ){
        count++;
	flag=0;
    }
    else if ( !flag && ( (s[i]>='a' && s[i]<='z') || 
     (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9') ) ) flag=1;
    i++;
  }
  return count;
}

void initialize(int *i, int *counter, int *flag, int *k){
  *i=0;
  *counter=0;
  *flag=1;
  *k=0;
}

char **string_to_words(char *s){
  char **array;
  int counter, i, flag, j, k, temp;
  counter=count(s);
  if (counter==0) return NULL;
  array=malloc(sizeof(char *)*(counter+1));
  if (array==NULL) return NULL;
  initialize(&i,&counter,&flag,&k);
  while(s[i]){
    counter++;
    if ( !((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') 
	   || (s[i]>='0' && s[i]<='9')) && flag ) flag=0;
    else if ( !flag && ( (s[i]>='a' && s[i]<='z') || (s[i]>='A' 
	   && s[i]<='Z') || (s[i]>='0' && s[i]<='9') ) ) flag=1;
    if (!flag){ counter--;
      if (counter!=0){
	array[k]=malloc(sizeof(char)*counter+1);
	if (array[k]==NULL){
	  while (k>=0){
	    free(array[k]);
	    k--;
	  } free(array);
	  return NULL;
	} j=counter;
	temp=0;
	while (j>0){
	  array[k][temp]=s[i-j];
	  temp++;
	  j--;
	} array[k][temp]='\0';
	k++;
      } counter=0;
    } i++;
  } array[k]=NULL;
  return array;  
}

/*void free_it(char **w){
  int i;
  i=0;
  while (w[i]){
    free(w[i]);
    i++;
  }
  free(w);
}*/
