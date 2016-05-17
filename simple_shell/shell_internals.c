#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"
/*after user sends command, initial processsing is done*/
void initial_processing(char **args, char **envp){
  int z;
  handle_comments(args);
  for (z=0;args[z];z++){
    char *temp;
    char **names;
    if ( (names=v_names(args[z])) ){
      temp=replace_variable_names(args[z], names, envp );
      free(args[z]);
      args[z]=temp;
    }
  }
}

/*for $?*/
void check_convert_dollar_question(char **args, int status){
  int i,k, length;
  char a[4];
  convert_error_int_to_string(status, a);
  for (i=0; args[i];i++){
    if (args[i][0]=='$' && args[i][1]=='?' && args[i][2]=='\0'){
      free(args[i]);
      length=string_length(a);
      args[i]=malloc(sizeof(char)*length+1);
      args[i][length]='\0';
      for (k=0;a[k];k++){
	args[i][k]=a[k];
      }
    }
  }
}

/*converts error to string for exit*/
void convert_error_int_to_string(int number, char *a){
  if (number<10){
    a[1]='\0';
    a[0]=(char)number+'0';
  }
  else if(number<100){
    a[2]='\0';
    a[1]=(number%10)+'0';
    a[0]=(number%10)+'0';
  }
  else if(number<999){
    a[3]='\0';
    a[2]=(number%10)+'0';
    a[1]=(number%10)+'0';
    a[0]=(number%10)+'0';
  }
}

/*returns variable names in the command*/
char **v_names(char *args){
  char **variables;
  int i, count, j, k;
  variables=NULL;
  k=0;
  for (count=0, i=0;args[i]!='\0';i++){
    if (args[i]=='$') count++;
  }
  if (count==0) return NULL;
  variables=malloc(sizeof(char *) * (count+1));
  variables[count]=NULL;
  for (i=0;args[i]!='\0';i++){
    if (args[i]=='$'){
      i++;
      count=0;
      for (j=i; (args[j]>='a' && args[j]<='z') || (args[j]>='A' && args[j]<='Z') || (args[j]=='_'); j++){
	count++;
      }
      variables[k]=malloc(sizeof(char)*(count+2));
      variables[k][0]='$';
      variables[k][count+1]='\0';
      for (count=1; (args[i]>='a' && args[i]<='z') || (args[i]>='A' && args[i]<='Z') || (args[i]=='_'); i++){
	variables[k][count]=args[i];
	count++;
      }
      k++;
      i--;
      if (args[j]=='\0') break;
    }
  }
  
  return variables;
}

/*replaces variable names in the command*/
char *replace_variable_names(char *args, char **names, char **envp){
  int i, length, count,p;
  char *evmnt, *new;
  p=0;
  length=string_length(args);
  for (i=0;names[i];i++){
    count=string_length(names[i]);
    length-=count;
    if ( (evmnt=get_env(names[i]+1, envp)) ){
      length+=string_length(evmnt+count);
    }
    
  }
  new=malloc(sizeof(char) * (length+1));
  new[length]='\0';
  for (count=0, i=0;args[i];){
    if (args[i]=='$'){
      length=string_length(names[p]);
      i+=length;
      if ( (evmnt=get_env(names[p]+1, envp)) ){
	p++;
	
	evmnt+=length;
	
	for (length=0;*(evmnt+length);count++, length++)
	  new[count]=*(evmnt+length);
      }
    }
    else{
      new[count]=args[i];
      count++;
      i++;
    }
    
  }
  free_tab(names);
  return new;
}
