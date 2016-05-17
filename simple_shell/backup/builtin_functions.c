#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"

int shell_cd(char **args, char ***envp){
	char *path;
	if (args[1]==NULL){
		if ( (path=get_env("HOME", *envp) ) ){
			if ( chdir(path+5) !=0 ){
				print_line("cd: $HOME not defined");
				print_char('\n');
				return 1;
			}
		}
	}
	else if (args[1][0]=='-' && args[1][1]=='\0' && args[2]==NULL){
		if ( (path=get_env("OLDPWD", *envp) ) ){
			if ( chdir(path+6) !=0 ){
				print_line("cd: $OLDPWD not defined");
				print_char('\n');
				return 1;
			}
		}
	}
	else{
		if ( chdir(args[1]) !=0 ){
			perror(args[1]);
			return 1;
		}
	}
	return 0;
}

int shell_exit(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon){
	int status;
	if (args[1]==NULL){
		free_tab(*envp);
		free_tab(args);
		free_tab(d_or);
		free_tab(d_ampersand);
		free_tab(semicolon);
		exit(0);
	}
	else if (args[2]==NULL){
		if ( ( status=convert_string_to_int(args[1]) ) == 0){
			print_line("exit: Usage: exit [0-255]\n");
			return 1;
		}
		free_tab(*envp);
		free_tab(args);
		free_tab(d_or);
		free_tab(d_ampersand);
		free_tab(semicolon);
		exit(status);
	}
	else{
		print_line("exit: Usage: exit [0-255]\n");
	}
	return 1;
}

int shell_env(__attribute__((unused)) char **args, char ***envp){
	print_tab(*envp);
	return 0;
}

int shell_setenv(char **args, char ***envp){
	char *line, **envp_new;
	int i, count;
	if (args[3]==NULL){ 
		count=string_length(args[1])+string_length(args[2]);
		if ( (i=get_env_index(args[1], *envp)) >= 0 ){
			free( (*envp)[i] );
			(*envp)[i]=malloc(sizeof(char)*(count+2));
			count=(write_to_str(args[1], (*envp)[i], '='))+1;
			write_to_index(args[2], (*envp)[i], '\0', count);
			return 0;
		}
		line=malloc(sizeof(char)*(count+2));
		i=(write_to_str(args[1], line, '='))+1;
		write_to_index(args[2], line, '\0', i);
		envp_new=add_envp(*envp, line);
		free(line);
		*envp=envp_new;
		return 0;
	}
	print_line("setenv: Usage: setenv VARIABLE VALUE");
	return 1;
}

int shell_unsetenv(char **args, char ***envp){
	char *line, **envp_new;
	if (args[2]==NULL){ 
		if ( (line=get_env(args[1], *envp)) ){
			envp_new=remove_envp(*envp, line);
			*envp=envp_new;
			return 0;
		}
		else{
			print_line(args[1]);
			print_line(" doesn't exist");
			return 1;
		}
	}
	print_line("setenv: Usage: unsetenv VARIABLE VALUE");
	return 1;
}

/*int shell_alias(char **args, char ***envp){
	int i,j, count;
	char **name;
	if (args[3]!=NULL) return 1;
	name=string_split(args[1],'=');
	for(j=0;args[1][j]!='"';j++);
	j++;
	for(i=0;args[i][j]!='"';i++){
		count++;
	}
	printf("ccc %d", count);
	return 0;
}*/


/*char *variable_name(char *source){
	int i, j, prev;
	for (i=0, source[i], i++){
		if (source[i]=='$'){
			prev=i;
			for (;source[i]; i++){

			}
		}
	}
}*/

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

/*void handle_variables(char **args, char **env){
	int i, j;
	for (i=0; args[i];i++){
		if (args[i]=='$'){

		}
	}
}*/

void handle_comments(char **args){
	int i,j;
	for (i=0;args[i];i++){
		if(args[i][0]=='#'){
			free(args[i]);
			for (j=i+1;args[j];j++){
				free(args[j]);
			}	
			args[i]=NULL;
			break;
		}
	}	
}

int shell_execute(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon, int status){
	char *builtin_str[] = {
  		"cd",
  		"env",
  		"setenv",
  		"unsetenv",
  		NULL
	};
	int (*built_in[])(char **, char ***)={
		&shell_cd,
		&shell_env,
		&shell_setenv,
		&shell_unsetenv,
	};

	/*int size=sizeof(builtin_str) / sizeof(char *);*/
	int i;
	check_convert_dollar_question(args, status);
	initial_processing(args, *envp);
	/*check_convert_dollar_question(args, status);*/
	/*if (args[0]=='\0') return 0;*/
	if (args[0]==NULL) return 0;
	for (i=0;builtin_str[i];i++){
		if ( strings_compare(args[0], builtin_str[i]) == 0 ){
			return built_in[i](args, envp);
		}
	}
	if ( strings_compare(args[0], "exit") == 0 ){
		return shell_exit(args, envp, d_or, d_ampersand, semicolon);
	}
	return shell_fork_and_run(args, *envp, d_or, d_ampersand, semicolon);
}

int strings_compare(const char *s1, const char *s2){
  int i;
  for (i=0;*(s1+i)==*(s2+i);i++){
    if (*(s1+i)=='\0')
      return 0;
  }
  return (*(s1+i)-*(s2+i));
}

int convert_string_to_int(char *source_string){
	int n=0;
	for(;*source_string;source_string++){
		if ( (*source_string<'0') || (*source_string>'9') ) return 0;
		n*=10;
		n=n +( ( (int)(*source_string) ) - '0' );
		if (n>255) return 0;
	}
	return n;
}
